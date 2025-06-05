/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextutils.h"
#include <QCoreApplication>
#include <QStandardPaths>

QString TextAutoGenerateText::TextAutoGenerateTextUtils::findExecutable(const QString &exec)
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
