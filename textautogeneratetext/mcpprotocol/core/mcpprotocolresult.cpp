/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolresult.h"
#include <QDebug>
#include <QJsonArray>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolResult::McpProtocolResult() = default;

McpProtocolResult::~McpProtocolResult() = default;

bool McpProtocolResult::operator==(const McpProtocolResult &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolResult &t)
{
    d.space() << "meta:" << t.meta();
    return d;
}

McpProtocolResult McpProtocolResult::fromJson(const QJsonObject &obj)
{
    McpProtocolResult prompt;
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

QJsonObject McpProtocolResult::toJson(const McpProtocolResult &boolean)
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

void McpProtocolResult::setAdditionalProperties(const QJsonObject &newAdditionalProperties)
{
    mAdditionalProperties = newAdditionalProperties;
}
