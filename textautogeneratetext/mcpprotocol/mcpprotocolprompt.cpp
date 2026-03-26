/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolprompt.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolPrompt::McpProtocolPrompt() = default;

McpProtocolPrompt::~McpProtocolPrompt() = default;

bool McpProtocolPrompt::operator==(const McpProtocolPrompt &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolPrompt &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "arguments:" << t.arguments();
    d.space() << "description:" << t.description();
    d.space() << "icons:" << t.icons();
    d.space() << "name:" << t.name();
    d.space() << "title:" << t.title();
    return d;
}

McpProtocolPrompt McpProtocolPrompt::fromJson(const QJsonObject &obj)
{
    McpProtocolPrompt prompt;
    // TODO
    return prompt;
}

QJsonObject McpProtocolPrompt::toJson(const McpProtocolPrompt &boolean)
{
    QJsonObject obj;
    obj["name"_L1] = boolean.name();
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }
    if (boolean.arguments().has_value()) {
        const auto arguments = *boolean.arguments();
        QJsonArray arr_arguments;
        for (const auto &v : arguments) {
            arr_arguments.append(McpProtocolPromptArgument::toJson(v));
        }
        obj["arguments"_L1] = arr_arguments;
    }
    if (boolean.description().has_value()) {
        obj["description"_L1] = *boolean.description();
    }
    if (boolean.icons().has_value()) {
        QJsonArray arr_icons;
        const auto icons = *boolean.icons();
        for (const auto &v : icons) {
            arr_icons.append(McpProtocolIcon::toJson(v));
        }
        obj["icons"_L1] = arr_icons;
    }
    if (boolean.title().has_value()) {
        obj["title"_L1] = *boolean.title();
    }

    return obj;
}

std::optional<McpProtocolMeta> McpProtocolPrompt::meta() const
{
    return mMeta;
}

void McpProtocolPrompt::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

std::optional<QList<McpProtocolPromptArgument>> McpProtocolPrompt::arguments() const
{
    return mArguments;
}

void McpProtocolPrompt::setArguments(std::optional<QList<McpProtocolPromptArgument>> newArguments)
{
    mArguments = std::move(newArguments);
}

std::optional<QString> McpProtocolPrompt::description() const
{
    return mDescription;
}

void McpProtocolPrompt::setDescription(std::optional<QString> newDescription)
{
    mDescription = std::move(newDescription);
}

std::optional<QList<McpProtocolIcon>> McpProtocolPrompt::icons() const
{
    return mIcons;
}

void McpProtocolPrompt::setIcons(std::optional<QList<McpProtocolIcon>> newIcons)
{
    mIcons = std::move(newIcons);
}

QString McpProtocolPrompt::name() const
{
    return mName;
}

void McpProtocolPrompt::setName(const QString &newName)
{
    mName = newName;
}

std::optional<QString> McpProtocolPrompt::title() const
{
    return mTitle;
}

void McpProtocolPrompt::setTitle(std::optional<QString> newTitle)
{
    mTitle = std::move(newTitle);
}
