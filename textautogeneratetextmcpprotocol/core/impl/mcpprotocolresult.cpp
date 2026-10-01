/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolresult.h"
#include <QDebug>
#include <QSet>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolResult::McpProtocolResult() = default;

bool McpProtocolResult::operator==(const McpProtocolResult &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolResult &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "additionalProperties:" << t.additionalProperties();
    return d;
}

McpProtocolResult McpProtocolResult::fromJson(const QJsonObject &obj)
{
    McpProtocolResult prompt;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    {
        const QSet<QString> knownKeys{"_meta"_L1};
        QJsonObject additionalObjs;
        for (auto it = obj.constBegin(); it != obj.constEnd(); ++it) {
            if (!knownKeys.contains(it.key())) {
                additionalObjs.insert(it.key(), it.value());
            }
        }
        prompt.setAdditionalProperties(std::move(additionalObjs));
    }
    return prompt;
}

QJsonObject McpProtocolResult::toJson(const McpProtocolResult &result)
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

std::optional<McpProtocolMeta> McpProtocolResult::meta() const
{
    return mMeta;
}

void McpProtocolResult::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

QJsonObject McpProtocolResult::additionalProperties() const
{
    return mAdditionalProperties;
}

void McpProtocolResult::setAdditionalProperties(QJsonObject newAdditionalProperties)
{
    mAdditionalProperties = std::move(newAdditionalProperties);
}
