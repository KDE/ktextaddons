/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolinitializeresult.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <utility>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolInitializeResult::McpProtocolInitializeResult() = default;

McpProtocolInitializeResult::~McpProtocolInitializeResult() = default;

bool McpProtocolInitializeResult::operator==(const McpProtocolInitializeResult &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeResult &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "resources:" << t.instructions();
    d.space() << "protocolVersion:" << t.protocolVersion();
    d.space() << "serverInfo:" << t.serverInfo();
    return d;
}

McpProtocolInitializeResult McpProtocolInitializeResult::fromJson(const QJsonObject &obj)
{
    McpProtocolInitializeResult prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(obj["_meta"_L1].toObject()));
    }
    return prompt;
}

QJsonObject McpProtocolInitializeResult::toJson(const McpProtocolInitializeResult &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolInitializeResult::meta() const
{
    return mMeta;
}

void McpProtocolInitializeResult::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

std::optional<QString> McpProtocolInitializeResult::instructions() const
{
    return mInstructions;
}

void McpProtocolInitializeResult::setInstructions(std::optional<QString> newInstructions)
{
    mInstructions = newInstructions;
}

QString McpProtocolInitializeResult::protocolVersion() const
{
    return mProtocolVersion;
}

void McpProtocolInitializeResult::setProtocolVersion(const QString &newProtocolVersion)
{
    mProtocolVersion = newProtocolVersion;
}

McpProtocolImplementation McpProtocolInitializeResult::serverInfo() const
{
    return mServerInfo;
}

void McpProtocolInitializeResult::setServerInfo(const McpProtocolImplementation &newServerInfo)
{
    mServerInfo = newServerInfo;
}
