/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolcommonutils.h"
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolMeta>

#include <QJsonValue>
#include <QMap>
#include <QRandomGenerator>
#include <QRegularExpression>
#include <QUuid>

#include <array>
using namespace TextAutoGenerateTextMcpProtocolCore;
using namespace Qt::Literals::StringLiterals;

QString McpProtocolCommonUtils::serverConfigFileName()
{
    return u"mcpprotocolserver"_s;
}

QByteArray McpProtocolCommonUtils::generateUUid()
{
    return QUuid::createUuid().toByteArray(QUuid::Id128);
}

QStringList McpProtocolCommonUtils::mcpServerList(const KSharedConfig::Ptr &config)
{
    static const QRegularExpression regularExpression(u"^Mcp Server #\\d+$"_s);
    return config->groupList().filter(regularExpression);
}

QByteArray McpProtocolCommonUtils::generateAuthToken()
{
    std::array<quint32, 8> data; // 32 bytes
    QRandomGenerator::system()->fillRange(data.data(), data.size());
    return QByteArray(reinterpret_cast<const char *>(data.data()), sizeof(data)).toBase64(QByteArray::Base64UrlEncoding | QByteArray::OmitTrailingEquals);
}

QString McpProtocolCommonUtils::metaGroupName()
{
    return u"org.kde/group"_s;
}

QString McpProtocolCommonUtils::metaGroupTitle()
{
    return u"org.kde/groupTitle"_s;
}

void McpProtocolCommonUtils::addToolMeta(TextAutoGenerateTextMcpProtocolCore::McpProtocolMeta &meta, const QString &groupName, const QString &groupTitle)
{
    auto newMeta = meta.meta().value_or(QMap<QString, QJsonValue>{});
    newMeta.insert(metaGroupName(), groupName);
    newMeta.insert(metaGroupTitle(), groupTitle);
    meta.setMeta(newMeta);
}
