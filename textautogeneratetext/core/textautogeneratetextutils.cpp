/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextutils.h"
using namespace Qt::Literals::StringLiterals;

#include <QCoreApplication>
#include <QStandardPaths>
using namespace TextAutoGenerateText;
QString TextAutoGenerateTextUtils::findExecutable(const QString &exec)
{
#ifdef Q_OS_WIN
    const QString executableName = exec + u".exe"_s;
    QString path = QStandardPaths::findExecutable(executableName, {QCoreApplication::applicationDirPath()});
    if (path.isEmpty()) {
        path = QStandardPaths::findExecutable(executableName);
    }
#else
    const QString path = QStandardPaths::findExecutable(exec);
#endif
    return path;
}
