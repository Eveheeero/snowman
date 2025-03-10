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

#include "ParseError.h"

namespace nc {
namespace core {
namespace input {

QString ParseError::unicodeWhat() const noexcept {
    const int *line = boost::get_error_info<ErrorLine>(*this);
    const int *column = boost::get_error_info<ErrorColumn>(*this);

    if (line && column) {
        return tr("%1:%2: %3").arg(*line).arg(*column).arg(Exception::unicodeWhat());
    }

    if (const ByteSize *offset = boost::get_error_info<ErrorOffset>(*this)) {
        return tr("offset 0x%1: %2").arg(*offset, 0, 16).arg(Exception::unicodeWhat());
    }

    return Exception::unicodeWhat();
}

} // namespace input
} // namespace core
} // namespace nc

/* vim:set et sts=4 sw=4: */
