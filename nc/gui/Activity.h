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
#include <QRunnable>

namespace nc {
namespace gui {

/**
 * Base class for background activities.
 */
class Activity : public QObject, public QRunnable {
    Q_OBJECT

public:
    /**
     * Does the work and emits the finished() signal.
     */
    void run() override;

protected:
    /**
     * This function does the real work.
     * Override it in subclasses.
     */
    virtual void work() = 0;

Q_SIGNALS:

    /**
     * This signal is emitted when the activity has finished execution.
     */
    void finished();
};

} // namespace gui
} // namespace nc

/* vim:set et sts=4 sw=4: */
