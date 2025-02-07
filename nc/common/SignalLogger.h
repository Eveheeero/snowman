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

#include <QObject>

#include "Logger.h"

namespace nc {

/**
 * Logger converting log() calls to signals.
 */
class SignalLogger : public QObject, public nc::Logger {
    Q_OBJECT

public:
    void log(LogLevel level, const QString &text) override;

    Q_SIGNAL
    /**
     * Signal emitted when there is a message to be logged.
     *
     * \param message Formatted log message.
     */
    void onMessage(const QString &message);
};

} // namespace nc

/* vim:set et sts=4 sw=4: */
