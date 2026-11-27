/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textutilscolorshell.h"

#include <cstdio>
#ifdef Q_OS_WIN
#include <io.h>
#else
#include <unistd.h>
#endif

using namespace TextUtils;
using namespace Qt::Literals::StringLiterals;

bool TextUtilsColorShell::useAnsiFormatting()
{
    static const bool enabled = [] {
        if (!qEnvironmentVariableIsEmpty("NO_COLOR")) {
            return false;
        }
        if (qgetenv("TERM") == "dumb") {
            return false;
        }
#ifdef Q_OS_WIN
        return _isatty(_fileno(stdout)) != 0;
#else
        return isatty(fileno(stdout)) != 0;
#endif
    }();
    return enabled;
}

QString TextUtilsColorShell::ansi(const QString &text, QLatin1StringView on, QLatin1StringView off)
{
    if (!useAnsiFormatting()) {
        return text;
    }
    return on + text + off;
}

QString TextUtilsColorShell::bold(const QString &text)
{
    return ansi(text, "\x1b[1m"_L1, "\x1b[22m"_L1);
}

QString TextUtilsColorShell::dim(const QString &text)
{
    return ansi(text, "\x1b[2m"_L1, "\x1b[22m"_L1);
}

QString TextUtilsColorShell::cyan(const QString &text)
{
    return ansi(text, "\x1b[36m"_L1, "\x1b[39m"_L1);
}

QString TextUtilsColorShell::underline(const QString &text)
{
    return ansi(text, "\x1b[4m"_L1, "\x1b[4m"_L1);
}
