/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolelicitrequestformparams.h"
#include <QDebug>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolElicitRequestFormParams::McpProtocolElicitRequestFormParams() = default;
McpProtocolElicitRequestFormParams::~McpProtocolElicitRequestFormParams() = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestFormParams &t)
{
    // TODO
    return d;
}

std::optional<McpProtocolUtils::ProgressToken> McpProtocolElicitRequestFormParams::Meta::progressToken() const
{
    return mProgressToken;
}

void McpProtocolElicitRequestFormParams::Meta::setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken)
{
    mProgressToken = std::move(newProgressToken);
}

McpProtocolElicitRequestFormParams McpProtocolElicitRequestFormParams::fromJson(const QJsonObject &obj)
{
    // TODO
    return {};
}

QJsonObject McpProtocolElicitRequestFormParams::toJson(const McpProtocolElicitRequestFormParams &image)
{
    // TODO
    return {};
}

QString McpProtocolElicitRequestFormParams::message() const
{
    return mMessage;
}

void McpProtocolElicitRequestFormParams::setMessage(const QString &newMessage)
{
    mMessage = newMessage;
}

std::optional<McpProtocolTaskMetadata> McpProtocolElicitRequestFormParams::task() const
{
    return mTask;
}

void McpProtocolElicitRequestFormParams::setTask(std::optional<McpProtocolTaskMetadata> newTask)
{
    mTask = std::move(newTask);
}
