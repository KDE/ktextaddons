/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoltool.h"
#include <QDebug>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolTool::McpProtocolTool() = default;

McpProtocolTool::~McpProtocolTool() = default;

bool McpProtocolTool::operator==(const McpProtocolTool &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolTool &t)
{
    return d;
}

McpProtocolTool McpProtocolTool::fromJson(const QJsonObject &obj)
{
    McpProtocolTool text;
    return text;
}

QJsonObject McpProtocolTool::toJson(const McpProtocolTool &text)
{
    QJsonObject obj;
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolTool::meta() const
{
    return mMeta;
}

void McpProtocolTool::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

std::optional<McpProtocolToolAnnotations> McpProtocolTool::annotations() const
{
    return mAnnotations;
}

void McpProtocolTool::setAnnotations(std::optional<McpProtocolToolAnnotations> newAnnotations)
{
    mAnnotations = std::move(newAnnotations);
}

std::optional<QString> McpProtocolTool::description() const
{
    return mDescription;
}

void McpProtocolTool::setDescription(std::optional<QString> newDescription)
{
    mDescription = std::move(newDescription);
}

std::optional<McpProtocolToolExecution> McpProtocolTool::execution() const
{
    return mExecution;
}

void McpProtocolTool::setExecution(std::optional<McpProtocolToolExecution> newExecution)
{
    mExecution = std::move(newExecution);
}

std::optional<QList<McpProtocolIcon>> McpProtocolTool::icons() const
{
    return mIcons;
}

void McpProtocolTool::setIcons(std::optional<QList<McpProtocolIcon>> newIcons)
{
    mIcons = std::move(newIcons);
}

McpProtocolTool::InputSchema McpProtocolTool::inputSchema() const
{
    return mInputSchema;
}

void McpProtocolTool::setInputSchema(const InputSchema &newInputSchema)
{
    mInputSchema = newInputSchema;
}

QString McpProtocolTool::name() const
{
    return mName;
}

void McpProtocolTool::setName(const QString &newName)
{
    mName = newName;
}

std::optional<McpProtocolTool::OutputSchema> McpProtocolTool::outputSchema() const
{
    return mOutputSchema;
}

void McpProtocolTool::setOutputSchema(std::optional<OutputSchema> newOutputSchema)
{
    mOutputSchema = std::move(newOutputSchema);
}

std::optional<QString> McpProtocolTool::title() const
{
    return mTitle;
}

void McpProtocolTool::setTitle(std::optional<QString> newTitle)
{
    mTitle = std::move(newTitle);
}

bool McpProtocolTool::InputSchema::operator==(const InputSchema &other) const = default;

bool McpProtocolTool::OutputSchema::operator==(const OutputSchema &other) const = default;
