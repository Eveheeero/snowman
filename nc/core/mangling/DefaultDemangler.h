/* The file is part of Snowman decompiler. */
/* See doc/licenses.asciidoc for the licensing information. */

#pragma once

#include <nc/config.h>

#include "Demangler.h"

namespace nc {
namespace core {
namespace mangling {

/**
 * A simple demangler delegating all the work to
 * __cxa_demangle and __unDName.
 */
class DefaultDemangler : public Demangler {
public:
    QString demangle(const QString &symbol) const override;
};

} // namespace mangling
} // namespace core
} // namespace nc

/* vim:set et sts=4 sw=4: */
