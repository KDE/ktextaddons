/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolpromptargument.h"
#include <QDebug>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolPromptArgument::McpProtocolPromptArgument() = default;

McpProtocolPromptArgument::~McpProtocolPromptArgument() = default;

bool McpProtocolPromptArgument::operator==(const McpProtocolPromptArgument &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolPromptArgument &t)
{
    d.space() << "description:" << t.description();
    d.space() << "name:" << t.name();
    d.space() << "required:" << t.required();
    d.space() << "title:" << t.title();
    return d;
}

McpProtocolPromptArgument McpProtocolPromptArgument::fromJson(const QJsonObject &obj)
{
    McpProtocolPromptArgument prompt;
    if (obj.contains("description"_L1)) {
        prompt.setDescription(obj.value("description"_L1).toString());
    }
    prompt.setName(obj.value("name"_L1).toString());
    if (obj.contains("required"_L1)) {
        prompt.setRequired(obj.value("required"_L1).toBool());
    }
    if (obj.contains("title"_L1)) {
        prompt.setTitle(obj.value("title"_L1).toString());
    }
    return prompt;
}

QJsonObject McpProtocolPromptArgument::toJson(const McpProtocolPromptArgument &prompt)
{
    QJsonObject obj;
    obj["name"_L1] = prompt.name();
    if (prompt.description().has_value()) {
        obj["description"_L1] = *prompt.description();
    }
    if (prompt.required().has_value()) {
        obj["required"_L1] = *prompt.required();
    }
    if (prompt.title().has_value()) {
        obj["title"_L1] = *prompt.title();
    }
    return obj;
}

std::optional<QString> McpProtocolPromptArgument::description() const
{
    return mDescription;
}

void McpProtocolPromptArgument::setDescription(std::optional<QString> newDescription)
{
    mDescription = std::move(newDescription);
}

QString McpProtocolPromptArgument::name() const
{
    return mName;
}

void McpProtocolPromptArgument::setName(const QString &newName)
{
    mName = newName;
}

std::optional<bool> McpProtocolPromptArgument::required() const
{
    return mRequired;
}

void McpProtocolPromptArgument::setRequired(std::optional<bool> newRequired)
{
    mRequired = std::move(newRequired);
}

std::optional<QString> McpProtocolPromptArgument::title() const
{
    return mTitle;
}

void McpProtocolPromptArgument::setTitle(std::optional<QString> newTitle)
{
    mTitle = std::move(newTitle);
}
