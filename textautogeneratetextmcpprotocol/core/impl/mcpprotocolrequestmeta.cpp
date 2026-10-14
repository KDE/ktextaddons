/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolrequestmeta.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolRequestMeta::McpProtocolRequestMeta() = default;

bool McpProtocolRequestMeta::operator==(const McpProtocolRequestMeta &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolRequestMeta &t)
{
    d.space() << "progressToken:" << t.progressToken();
    d.space() << "additionalProperties:" << t.additionalProperties();
    return d;
}

McpProtocolRequestMeta McpProtocolRequestMeta::fromJson(const QJsonObject &obj)
{
    McpProtocolRequestMeta meta;
    QJsonObject additionalProperties = obj;
    if (const QJsonValue progressTokenValue = obj.value("progressToken"_L1); progressTokenValue.isString() || progressTokenValue.isDouble()) {
        meta.setProgressToken(McpProtocolUtils::progressTokenFromJson(progressTokenValue));
        additionalProperties.remove("progressToken"_L1);
    } else if (!progressTokenValue.isUndefined()) {
        // Keep invalid value as is: it's saved again by toJson()
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolRequestMeta: invalid field 'progressToken'" << progressTokenValue;
    }
    meta.setAdditionalProperties(additionalProperties);
    return meta;
}

QJsonObject McpProtocolRequestMeta::toJson(const McpProtocolRequestMeta &meta)
{
    QJsonObject obj = meta.additionalProperties();
    if (meta.progressToken().has_value()) {
        obj["progressToken"_L1] = McpProtocolUtils::progressTokenToJson(*meta.progressToken());
    }
    return obj;
}

std::optional<McpProtocolUtils::ProgressToken> McpProtocolRequestMeta::progressToken() const
{
    return mProgressToken;
}

void McpProtocolRequestMeta::setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken)
{
    mProgressToken = std::move(newProgressToken);
}

QJsonObject McpProtocolRequestMeta::additionalProperties() const
{
    return mAdditionalProperties;
}

void McpProtocolRequestMeta::setAdditionalProperties(const QJsonObject &newAdditionalProperties)
{
    mAdditionalProperties = newAdditionalProperties;
}
