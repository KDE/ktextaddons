/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolcommonutils.h"

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
