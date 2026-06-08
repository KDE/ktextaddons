/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolelicitrequesturlparams.h"
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolElicitRequestURLParams::McpProtocolElicitRequestURLParams() = default;
McpProtocolElicitRequestURLParams::~McpProtocolElicitRequestURLParams() = default;

McpProtocolElicitRequestURLParams::Meta McpProtocolElicitRequestURLParams::Meta::fromJson(const QJsonObject &obj)
{
    McpProtocolElicitRequestURLParams::Meta meta;
    if (obj.contains("progressToken"_L1)) {
        meta.setProgressToken(McpProtocolUtils::progressTokenFromJson(obj["progressToken"_L1]));
    }
    return meta;
}

QJsonObject McpProtocolElicitRequestURLParams::Meta::toJson(const McpProtocolElicitRequestURLParams::Meta &image)
{
    QJsonObject obj;
    if (image.progressToken().has_value()) {
        obj["progressToken"_L1] = McpProtocolUtils::progressTokenToJson(*image.progressToken());
    }
    return obj;
}

std::optional<McpProtocolElicitRequestURLParams::Meta> McpProtocolElicitRequestURLParams::meta() const
{
    return mMeta;
}

void McpProtocolElicitRequestURLParams::setMeta(std::optional<Meta> newMeta)
{
    mMeta = std::move(newMeta);
}

QString McpProtocolElicitRequestURLParams::elicitationId() const
{
    return mElicitationId;
}

void McpProtocolElicitRequestURLParams::setElicitationId(const QString &newElicitationId)
{
    mElicitationId = newElicitationId;
}

QString McpProtocolElicitRequestURLParams::message() const
{
    return mMessage;
}

void McpProtocolElicitRequestURLParams::setMessage(const QString &newMessage)
{
    mMessage = newMessage;
}

std::optional<McpProtocolTaskMetadata> McpProtocolElicitRequestURLParams::task() const
{
    return mTask;
}

void McpProtocolElicitRequestURLParams::setTask(std::optional<McpProtocolTaskMetadata> newTask)
{
    mTask = std::move(newTask);
}

QString McpProtocolElicitRequestURLParams::url() const
{
    return mUrl;
}

void McpProtocolElicitRequestURLParams::setUrl(const QString &newUrl)
{
    mUrl = newUrl;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestURLParams &t)
{
    // TODO
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestURLParams::Meta &t)
{
    // TODO
    return d;
}

std::optional<McpProtocolUtils::ProgressToken> McpProtocolElicitRequestURLParams::Meta::progressToken() const
{
    return mProgressToken;
}

void McpProtocolElicitRequestURLParams::Meta::setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken)
{
    mProgressToken = std::move(newProgressToken);
}

bool TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestURLParams::Meta::operator==(const McpProtocolElicitRequestURLParams::Meta &other) const =
    default;

bool TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestURLParams::operator==(const McpProtocolElicitRequestURLParams &other) const = default;

McpProtocolElicitRequestURLParams TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestURLParams::fromJson(const QJsonObject &obj)
{
    // TODO
    return {};
}

QJsonObject TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestURLParams::toJson(const McpProtocolElicitRequestURLParams &image)
{
    // TODO
    return {};
}
