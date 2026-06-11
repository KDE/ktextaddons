/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolcanceltaskresult.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonArray>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolCancelTaskResult::McpProtocolCancelTaskResult() = default;

McpProtocolCancelTaskResult::~McpProtocolCancelTaskResult() = default;

bool McpProtocolCancelTaskResult::operator==(const McpProtocolCancelTaskResult &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCancelTaskResult &t)
{
    d.space() << "meta:" << t.meta();
    return d;
}

McpProtocolCancelTaskResult McpProtocolCancelTaskResult::fromJson(const QJsonObject &obj)
{
    McpProtocolCancelTaskResult prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(obj["_meta"_L1].toObject()));
    }
    return prompt;
}

QJsonObject McpProtocolCancelTaskResult::toJson(const McpProtocolCancelTaskResult &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolCancelTaskResult::meta() const
{
    return mMeta;
}

void McpProtocolCancelTaskResult::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}
