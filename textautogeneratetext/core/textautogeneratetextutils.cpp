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

QString TextAutoGenerateTextUtils::instanceConfigFileName()
{
    return u"autogeneratetextinstances"_s;
}

QStringList TextAutoGenerateTextUtils::instancesList(KConfig *config)
{
    static const QRegularExpression regularExpression(u"^Instance #\\d+$"_s);
    return config->groupList().filter(regularExpression);
}
