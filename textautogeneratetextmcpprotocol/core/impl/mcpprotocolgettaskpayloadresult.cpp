/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolgettaskpayloadresult.h"
#include <QDebug>
#include <QSet>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolGetTaskPayloadResult::McpProtocolGetTaskPayloadResult() = default;

bool McpProtocolGetTaskPayloadResult::operator==(const McpProtocolGetTaskPayloadResult &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolGetTaskPayloadResult &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "additionalProperties:" << t.additionalProperties();
    return d;
}

McpProtocolGetTaskPayloadResult McpProtocolGetTaskPayloadResult::fromJson(const QJsonObject &obj)
{
    McpProtocolGetTaskPayloadResult result;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        result.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    {
        const QSet<QString> knownKeys{"_meta"_L1};
        QJsonObject additionalObjs;
        for (auto it = obj.constBegin(); it != obj.constEnd(); ++it) {
            if (!knownKeys.contains(it.key())) {
                additionalObjs.insert(it.key(), it.value());
            }
        }
        result.setAdditionalProperties(std::move(additionalObjs));
    }
    return result;
}

QJsonObject McpProtocolGetTaskPayloadResult::toJson(const McpProtocolGetTaskPayloadResult &result)
{
    QJsonObject obj;
    if (result.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*result.meta());
    }
    const QJsonObject additionalProperties = result.additionalProperties();
    for (auto it = additionalProperties.constBegin(); it != additionalProperties.constEnd(); ++it) {
        obj.insert(it.key(), it.value());
    }
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolGetTaskPayloadResult::meta() const
{
    return mMeta;
}

void McpProtocolGetTaskPayloadResult::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

QJsonObject McpProtocolGetTaskPayloadResult::additionalProperties() const
{
    return mAdditionalProperties;
}

void McpProtocolGetTaskPayloadResult::setAdditionalProperties(QJsonObject newAdditionalProperties)
{
    mAdditionalProperties = std::move(newAdditionalProperties);
}
