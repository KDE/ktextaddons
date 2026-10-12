/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextutils.h"

#include <KConfig>
#include <QCoreApplication>
#include <QRegularExpression>
#include <QStandardPaths>
#include <QUuid>
using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;

QString TextAutoGenerateTextUtils::instanceConfigFileName()
{
    return u"autogeneratetextinstances"_s;
}

QStringList TextAutoGenerateTextUtils::instancesList(const KSharedConfig::Ptr &config)
{
    static const QRegularExpression regularExpression(u"^Instance #\\d+$"_s);
    return config->groupList().filter(regularExpression);
}

QByteArray TextAutoGenerateTextUtils::generateUUid()
{
    return QUuid::createUuid().toByteArray(QUuid::Id128);
}

QString TextAutoGenerateTextUtils::promptConfigFileName()
{
    return u"autogeneratetextprompts"_s;
}

QStringList TextAutoGenerateTextUtils::promptsList(const KSharedConfig::Ptr &config)
{
    static const QRegularExpression regularExpression(u"^Prompt #\\d+$"_s);
    return config->groupList().filter(regularExpression);
}
