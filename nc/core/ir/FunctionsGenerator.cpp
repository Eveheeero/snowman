/* The file is part of Snowman decompiler. */
/* See doc/licenses.asciidoc for the licensing information. */

//
// SmartDec decompiler - SmartDec is a native code to C/C++ decompiler
// Copyright (C) 2015 Alexander Chernov, Katerina Troshina, Yegor Derevenets,
// Alexander Fokin, Sergey Levin, Leonid Tsvetkov
//
// This file is part of SmartDec decompiler.
//
// SmartDec decompiler is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// SmartDec decompiler is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with SmartDec decompiler.  If not, see <http://www.gnu.org/licenses/>.
//

#include "FunctionsGenerator.h"

#include <boost/range/adaptor/map.hpp>
#include <boost/unordered_set.hpp>

#include <nc/common/Foreach.h>
#include <nc/common/Range.h>

#include "BasicBlock.h"
#include "CFG.h"
#include "Function.h"
#include "Functions.h"
#include "Jump.h"
#include "Program.h"
#include "Statements.h"

#include <nc/core/arch/Instruction.h>

namespace nc {
namespace core {
namespace ir {

namespace {

void dfs(const CFG &cfg, const BasicBlock *basicBlock, boost::unordered_set<const BasicBlock *> &visited,
         std::vector<const BasicBlock *> &trace) {
    visited.insert(basicBlock);
    trace.push_back(basicBlock);

    // A코드블럭에서 다른 코드블록으로 이동하는 명령을 찾아 가지처럼 연결함
    foreach (const BasicBlock *successor, cfg.getSuccessors(basicBlock)) {
        // 이전에 분석했던 블록이면 무시함
        if (visited.find(successor) == visited.end()) {
            dfs(cfg, successor, visited, trace);
        }
    }
}

} // anonymous namespace

/**
 * @brief 여러 블럭 이동 패턴을 이용해, 어떤 것이 함수인지 생성한다
 */
void FunctionsGenerator::makeFunctions(const Program &program, Functions &functions) const {
    boost::unordered_set<const BasicBlock *> processed;

    CFG cfg(program.basicBlocks());

    auto addFunction = [&](const std::vector<const BasicBlock *> &basicBlocks, const BasicBlock *entry) {
        auto function = makeFunction(basicBlocks, entry);
        if (function->isEmpty()) {
            return;
        }

        /*
         * If the function's entry starts with some no-ops, move the function's
         * entry's address to the first meaningful instruction, unless somebody
         * calls it using current address.
         */
        // 0x90 0x90으로 시작하면 알맞는 인스트럭션을 만날때까지 이동하는듯하다?
        if (function->entry() && function->entry()->address() && function->entry()->statements().front() &&
            function->entry()->statements().front()->instruction() &&
            *function->entry()->address() != function->entry()->statements().front()->instruction()->addr()) {
            assert(*function->entry()->address() < function->entry()->statements().front()->instruction()->addr());
            if (!program.isCalledAddress(*function->entry()->address())) {
                function->entry()->setAddress(function->entry()->statements().front()->instruction()->addr());
            }
        }

        functions.addFunction(std::move(function));
    };

    /* jump나 call의 목적지부터 함수를 생성한다 */
    foreach (const BasicBlock *basicBlock, program.basicBlocks()) {
        // 블럭의 시작이 call에 의해 불러지고 있으면
        if (basicBlock->address() && program.isCalledAddress(*basicBlock->address())) {
            boost::unordered_set<const BasicBlock *> visited;
            std::vector<const BasicBlock *> trace;

            dfs(cfg, basicBlock, visited, trace);
            // 해당 함수를 타게 되면 어떤 순서대로 함수를 타는지 분석 (trace가 어떤 순서대로 함수를 타는지 기록한 것)
            addFunction(trace, basicBlock);
            processed.insert(trace.begin(), trace.end());
        }
    }

    /* 독립된 함수들 분석 */
    foreach (const BasicBlock *basicBlock, program.basicBlocks()) {
        // 어디에서도 해당 함수에 온 적 없으면서, 분석도 한 적 없으면 분석한다. (외부호출?)
        if (basicBlock->address() && cfg.getPredecessors(basicBlock).empty() && !contains(processed, basicBlock)) {
            std::vector<const BasicBlock *> trace;

            dfs(cfg, basicBlock, processed, trace);
            addFunction(trace, basicBlock);
        }
    }

    /* 다른데서 해당 함수를 참조했지만 분석한 적 없으면 분석 */
    foreach (const BasicBlock *basicBlock, program.basicBlocks()) {
        if (basicBlock->address() && !contains(processed, basicBlock)) {
            std::vector<const BasicBlock *> trace;

            dfs(cfg, basicBlock, processed, trace);
            addFunction(trace, basicBlock);
        }
    }
}

/**
 * @param basicBlocks 해당 함수는 내부적으로 어떤 어셈블리 블럭을 타는지
 * @param entry 시작 함수블럭
 */
std::unique_ptr<Function> FunctionsGenerator::makeFunction(const std::vector<const BasicBlock *> &basicBlocks,
                                                           const BasicBlock *entry) const {
    assert(!basicBlocks.empty());

    /* Create a new function. */
    std::unique_ptr<Function> function(new Function);

    /* 해당 함수가 어떤 인스트럭션 블럭을 거쳐가는지 파악 */
    auto clones = cloneIntoFunction(basicBlocks, function.get());

    /* 함수의 시작 블럭 설정 */
    if (entry) {
        BasicBlock *clonedEntry = nc::find(clones, entry);
        assert(clonedEntry != nullptr && "Entry must have been cloned.");

        function->setEntry(clonedEntry);
    }

    return function;
}

FunctionsGenerator::BasicBlockMap
FunctionsGenerator::cloneIntoFunction(const std::vector<const BasicBlock *> &basicBlocks, Function *function) {
    BasicBlockMap clones;

    /*
     * Clone basic blocks.
     */
    foreach (const BasicBlock *basicBlock, basicBlocks) {
        auto clone = basicBlock->clone();
        clones[basicBlock] = clone.get();
        function->addBasicBlock(std::move(clone));
    }

    /*
     * This function replaces all pointers to basic blocks in a jump target
     * by the pointers to their clones.
     */
    auto updateJumpTarget = [&](JumpTarget &target) {
        if (target.basicBlock()) {
            target.setBasicBlock(nc::find(clones, target.basicBlock()));
        }
        if (target.table()) {
            foreach (JumpTableEntry &entry, *target.table()) {
                entry.setBasicBlock(nc::find(clones, entry.basicBlock()));
            }
        }
    };

    /*
     * Update jump targets.
     */
    foreach (BasicBlock *basicBlock, clones | boost::adaptors::map_values) {
        if (ir::Jump *jump = basicBlock->getJump()) {
            updateJumpTarget(jump->thenTarget());
            updateJumpTarget(jump->elseTarget());

            /* Remove jumps to direct successors that were not cloned. */
            if (jump->isUnconditional() && !jump->thenTarget()) {
                basicBlock->statements().pop_back();
            }
        }
    }

    return clones;
}

} // namespace ir
} // namespace core
} // namespace nc

/* vim:set et sts=4 sw=4: */
