/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextutils.h"

#include <KConfig>
#include <QCoreApplication>
#include <QRegularExpression>
#include <QStandardPaths>
using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
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

QString TextAutoGenerateTextUtils::instanceConfigFileName()
{
    return u"autogeneratetextinstances"_s;
}

QStringList TextAutoGenerateTextUtils::instancesList(KConfig *config)
{
    static const QRegularExpression regExpr(u"^Instance #\\d+$"_s);
    return config->groupList().filter(regExpr);
}
