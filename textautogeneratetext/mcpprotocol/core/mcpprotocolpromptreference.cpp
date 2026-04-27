/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolpromptreference.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolPromptReference::McpProtocolPromptReference() = default;

McpProtocolPromptReference::~McpProtocolPromptReference() = default;

QByteArray McpProtocolPromptReference::type()
{
    return "ref/prompt"_ba;
}

bool McpProtocolPromptReference::operator==(const McpProtocolPromptReference &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolPromptReference &t)
{
    d.space() << "name:" << t.name();
    d.space() << "title:" << t.title();
    return d;
}

McpProtocolPromptReference McpProtocolPromptReference::fromJson(const QJsonObject &obj)
{
    McpProtocolPromptReference prompt;
    prompt.setName(obj.value("name"_L1).toString());
    if (obj.contains("title"_L1))
        prompt.setTitle(obj.value("title"_L1).toString());
    if (obj.value("type"_L1).toString() != QString::fromLatin1(McpProtocolPromptReference::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'type' must be 'ref/prompt', got: " << obj.value("type"_L1).toString();
    }
    return prompt;
}

QJsonObject McpProtocolPromptReference::toJson(const McpProtocolPromptReference &boolean)
{
    QJsonObject obj;
    obj["name"_L1] = boolean.name();
    obj["type"_L1] = QString::fromLatin1(McpProtocolPromptReference::type());
    if (boolean.title().has_value()) {
        obj.insert("title"_L1, *boolean.title());
    }
    return obj;
}

QString McpProtocolPromptReference::name() const
{
    return mName;
}

void McpProtocolPromptReference::setName(const QString &newName)
{
    mName = newName;
}

std::optional<QString> McpProtocolPromptReference::title() const
{
    return mTitle;
}

void McpProtocolPromptReference::setTitle(std::optional<QString> newTitle)
{
    mTitle = newTitle;
}
