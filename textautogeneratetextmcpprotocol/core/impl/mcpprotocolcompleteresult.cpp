/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolcompleteresult.h"
#include <QDebug>
#include <QJsonArray>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolCompleteResult::McpProtocolCompleteResult() = default;

McpProtocolCompleteResult::~McpProtocolCompleteResult() = default;

bool McpProtocolCompleteResult::operator==(const McpProtocolCompleteResult &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCompleteResult &t)
{
    d.space() << "meta:" << t.meta();
    return d;
}

McpProtocolCompleteResult McpProtocolCompleteResult::fromJson(const QJsonObject &obj)
{
    McpProtocolCompleteResult prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(obj["_meta"_L1].toObject()));
    }
    // TODO
    return prompt;
}

QJsonObject McpProtocolCompleteResult::toJson(const McpProtocolCompleteResult &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }
    // TODO
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolCompleteResult::meta() const
{
    return mMeta;
}

void McpProtocolCompleteResult::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}
