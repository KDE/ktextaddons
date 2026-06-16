/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolgettaskpayloadresult.h"
#include <QDebug>
#include <QJsonArray>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolGetTaskPayloadResult::McpProtocolGetTaskPayloadResult() = default;

McpProtocolGetTaskPayloadResult::~McpProtocolGetTaskPayloadResult() = default;

bool McpProtocolGetTaskPayloadResult::operator==(const McpProtocolGetTaskPayloadResult &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolGetTaskPayloadResult &t)
{
    d.space() << "meta:" << t.meta();
    return d;
}

McpProtocolGetTaskPayloadResult McpProtocolGetTaskPayloadResult::fromJson(const QJsonObject &obj)
{
    McpProtocolGetTaskPayloadResult prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(obj["_meta"_L1].toObject()));
    }
    {
        const QSet<QString> knownKeys{"_meta"_L1};
        QJsonObject additionalObjs;
        for (auto it = obj.constBegin(); it != obj.constEnd(); ++it) {
            if (!knownKeys.contains(it.key())) {
                additionalObjs.insert(it.key(), it.value());
            }
        }
        prompt.setAdditionalProperties(additionalObjs);
    }
    return prompt;
}

QJsonObject McpProtocolGetTaskPayloadResult::toJson(const McpProtocolGetTaskPayloadResult &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }
    for (auto it = boolean.additionalProperties().constBegin(); it != boolean.additionalProperties().constEnd(); ++it) {
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

void McpProtocolGetTaskPayloadResult::setAdditionalProperties(const QJsonObject &newAdditionalProperties)
{
    mAdditionalProperties = newAdditionalProperties;
}
