/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolgetpromptresult.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolGetPromptResult::McpProtocolGetPromptResult() = default;

McpProtocolGetPromptResult::~McpProtocolGetPromptResult() = default;

bool McpProtocolGetPromptResult::operator==(const McpProtocolGetPromptResult &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolGetPromptResult &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "description:" << t.description();
    return d;
}

McpProtocolGetPromptResult McpProtocolGetPromptResult::fromJson(const QJsonObject &obj)
{
    McpProtocolGetPromptResult prompt;
    // TODO
    return prompt;
}

QJsonObject McpProtocolGetPromptResult::toJson(const McpProtocolGetPromptResult &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }
    if (boolean.description().has_value()) {
        obj["description"_L1] = *boolean.description();
    }
#if 0 // TODO
    QJsonArray messages;
    for (const auto &v : boolean.messages()) messages.append(toJson(v));
    obj.insert("messages", messages);
#endif
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolGetPromptResult::meta() const
{
    return mMeta;
}

void McpProtocolGetPromptResult::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

std::optional<QString> McpProtocolGetPromptResult::description() const
{
    return mDescription;
}

void McpProtocolGetPromptResult::setDescription(std::optional<QString> newDescription)
{
    mDescription = std::move(newDescription);
}
