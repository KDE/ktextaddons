/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolinitializeresult.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
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
    if (!obj.contains("capabilities"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: capabilities";
        return prompt;
    }
    if (!obj.contains("protocolVersion"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: protocolVersion";
        return prompt;
    }
    if (!obj.contains("serverInfo"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: serverInfo";
        return prompt;
    }
    if (obj.contains("capabilities"_L1) && obj["capabilities"_L1].isObject()) {
        // TODO prompt.setCapabilities = McpProtocolServerCapabilities::fromJson<>(obj["capabilities"_L1]);
    }
    if (obj.contains("instructions"_L1)) {
        prompt.setInstructions(obj.value("instructions"_L1).toString());
    }
    prompt.setProtocolVersion(obj["protocolVersion"_L1].toString());
    if (obj.contains("serverInfo"_L1) && obj["serverInfo"_L1].isObject()) {
        prompt.setServerInfo(McpProtocolImplementation::fromJson(obj["serverInfo"_L1].toObject()));
    }

    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(obj["_meta"_L1].toObject()));
    }
    return prompt;
}

QJsonObject McpProtocolInitializeResult::toJson(const McpProtocolInitializeResult &boolean)
{
    QJsonObject obj;
    // TODO obj["capabilities"_L1] = toJson(boolean.capabilities());
    obj["protocolVersion"_L1] = boolean.protocolVersion();
    obj["serverInfo"_L1] = McpProtocolImplementation::toJson(boolean.serverInfo());

    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }
    if (boolean.instructions().has_value()) {
        obj["instructions"_L1] = *boolean.instructions();
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
    mInstructions = std::move(newInstructions);
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
