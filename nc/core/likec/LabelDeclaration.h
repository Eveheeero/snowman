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

#include "Declaration.h"

namespace nc {
namespace core {
namespace likec {

/**
 * Label in function code.
 */
class LabelDeclaration : public Declaration {
    int referenceCount_; ///< Number of references to this label in the code.

public:
    /**
     * Class constructor.
     *
     * \param[in] identifier Name of the label.
     */
    explicit LabelDeclaration(QString identifier)
        : Declaration(LABEL_DECLARATION, std::move(identifier)), referenceCount_(0) {}

    /**
     * Increments reference count by the given delta.
     */
    void incReferenceCount(int delta = 1) { referenceCount_ += delta; }

    /**
     * \return Reference count.
     */
    int referenceCount() const { return referenceCount_; }
};

} // namespace likec
} // namespace core
} // namespace nc

NC_SUBCLASS(nc::core::likec::Declaration, nc::core::likec::LabelDeclaration,
            nc::core::likec::Declaration::LABEL_DECLARATION)

/* vim:set et sts=4 sw=4: */
