/* The file is part of Snowman decompiler. */
/* See doc/licenses.asciidoc for the licensing information. */

/* * SmartDec decompiler - SmartDec is a native code to C/C++ decompiler
 * Copyright (C) 2015 Alexander Chernov, Katerina Troshina, Yegor Derevenets,
 * Alexander Fokin, Sergey Levin, Leonid Tsvetkov
 *
 * This file is part of SmartDec decompiler.
 *
 * SmartDec decompiler is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SmartDec decompiler is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SmartDec decompiler.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <nc/config.h>

#include <QCoreApplication> /* For Q_DECLARE_TR_FUNCTIONS. */

namespace nc {
namespace core {

namespace ir {
class Function;

namespace calling {
class CalleeId;
}
} // namespace ir

class Context;

/**
 * 여러 종류의 분석을 알맞은 순서로 수행하는 클래스
 *
 * 아키텍쳐별로 다른 분석이 필요하면 해당 함수를 조작하여 기능 순서를 바꿀 수 있으며,
 * Architecture::setMasterAnalyzer()를 통해 등록할 수 있다.
 *
 * 메소드는 병렬적으로 실행될 수 있습니다. (현재는 한번에 하나만 실행을 하고 있다.)
 * 병렬적으로 수행하기 위해 모든 메소드는 정적 메소드입니다.
 */
class MasterAnalyzer {
    Q_DECLARE_TR_FUNCTIONS(MasterAnalyzer)

public:
    virtual ~MasterAnalyzer();

    /**
     * 인스트럭션에서 중간 분석 프로그램을 생성한다.
     */
    virtual void createProgram(Context &context) const;

    /**
     * 프로그램에서 함수들을 생성한다.
     */
    virtual void createFunctions(Context &context) const;

    /**
     * 후크를 생성한다.
     */
    virtual void createHooks(Context &context) const;

    virtual void detectCallingConventions(Context &context) const;

    /**
     * 함수의 호출 규약 감지
     *
     * \param calleeId 함수의 ID
     * @note fastcall이나 cdecl와 같은 함수 호출 규약을 감지한다.
     */
    virtual void detectCallingConvention(Context &context, const ir::calling::CalleeId &calleeId) const;

    /**
     * 모든 함수에 대한 흐름분석을 실행한다.
     *
     * @note 어떤 함수는 어떤 함수와 엮여있는지 등을 분석하는 것으로 추정된다.
     */
    virtual void dataflowAnalysis(Context &context) const;

    /**
     * 해당 함수에 대한 흐름분석을 실행한다.
     *
     * \param function 함수의 포인터
     * @note 해당 함수는 어떤 블록으로 진행되는지, 어떤 함수를 호출하는지 등을 분석하는 것으로 추정된다.
     */
    virtual void dataflowAnalysis(Context &context, ir::Function *function) const;

    /**
     * 함수의 이름을 재생성한다.
     *
     * @note 함수의 인자 등을 분석하는 것으로 추정된다.
     */
    virtual void reconstructSignatures(Context &context) const;

    /**
     * 로컬 및 전역변수를 생성한다.
     *
     * @note 사용되는 메모리를 기반으로 어느 메모리는 변수인지 등을 지정하는 것으로 추정된다.
     */
    virtual void reconstructVariables(Context &context) const;

    /**
     * 모든 함수에 대한 활성 분석을 실행한다.
     */
    virtual void livenessAnalysis(Context &context) const;

    /**
     * 해당 함수에 대한 활성 분석을 실행한다.
     *
     * \param function 함수의 포인터
     */
    virtual void livenessAnalysis(Context &context, const ir::Function *function) const;

    /**
     * 모든 함수에 대해 구조적 분석을 실행한다.
     */
    virtual void structuralAnalysis(Context &context) const;

    /**
     * 함수의 구조적 분석을 실행한다.
     *
     * \param function 함수의 포인터
     */
    virtual void structuralAnalysis(Context &context, const ir::Function *function) const;

    /**
     * 타입에 대한 정보를 연산한다.
     *
     * @note 해당 함수 부분에서 타입의 크기를 연산해 지정하는것으로 추정된다.
     */
    virtual void reconstructTypes(Context &context) const;

    /**
     * C프로그램같은 실행 흐름도를 작성한다.
     *
     * @note C프로그램처럼 for문이나 while문등을 작성하는것으로 추정된다.
     */
    virtual void generateTree(Context &context) const;

    /**
     * 어셈블리 프로그램을 디컴파일하는 전체 과정을 실행한다.
     */
    virtual void decompile(Context &context) const;

protected:
    /**
     * \param function 함수의 포인터
     *
     * \return 사용자에게 보여질 함수 이름
     */
    virtual QString getFunctionName(Context &context, const ir::Function *function) const;
};

} // namespace core
} // namespace nc

/* vim:set et sts=4 sw=4: */
