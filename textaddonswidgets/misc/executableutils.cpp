/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "executableutils.h"
#ifdef Q_OS_WIN
#include <QCoreApplication>
#endif
#include <QStandardPaths>

QString TextAddonsWidgets::ExecutableUtils::findExecutable(const QString &exec)
{
#ifdef Q_OS_WIN
    const QString executableName = exec + QStringLiteral(".exe");
    QString path = QStandardPaths::findExecutable(executableName, {QCoreApplication::applicationDirPath()});
    if (path.isEmpty()) {
        path = QStandardPaths::findExecutable(executableName);
    }
#else
    const QString path = QStandardPaths::findExecutable(exec);
#endif
    return path;
}

bool TextAddonsWidgets::ExecutableUtils::executableFound(const QString &exec)
{
    return !TextAddonsWidgets::ExecutableUtils::findExecutable(exec).isEmpty();
}
