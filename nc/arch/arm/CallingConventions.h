/* The file is part of Snowman decompiler. */
/* See doc/licenses.asciidoc for the licensing information. */

#pragma once

#include <nc/config.h>

#include <nc/core/ir/calling/Convention.h>

namespace nc {
namespace arch {
namespace arm {

class ArmArchitecture;

class DefaultCallingConvention : public core::ir::calling::Convention {
public:
    DefaultCallingConvention();
};

} // namespace arm
} // namespace arch
} // namespace nc

/* vim:set et sts=4 sw=4: */
