/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolutils.h"

#include <KConfig>
#include <QCoreApplication>
#include <QRegularExpression>
#include <QStandardPaths>
#include <QUuid>
using namespace TextAutoGenerateTextMcpProtocolCore;
using namespace Qt::Literals::StringLiterals;

QString McpProtocolUtils::serverConfigFileName()
{
    return u"mcpprotocolserver"_s;
}

QByteArray McpProtocolUtils::generateUUid()
{
    return QUuid::createUuid().toByteArray(QUuid::Id128);
}

QStringList McpProtocolUtils::mcpServerList(const KSharedConfig::Ptr &config)
{
    static const QRegularExpression regularExpression(u"^Mcp Server #\\d+$"_s);
    return config->groupList().filter(regularExpression);
}
