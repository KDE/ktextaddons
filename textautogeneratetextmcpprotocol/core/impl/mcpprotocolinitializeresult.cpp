/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolinitializeresult.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonObject>
#include <utility>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolInitializeResult::McpProtocolInitializeResult() = default;

bool McpProtocolInitializeResult::operator==(const McpProtocolInitializeResult &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeResult &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "instructions:" << t.instructions();
    d.space() << "protocolVersion:" << t.protocolVersion();
    d.space() << "serverInfo:" << t.serverInfo();
    d.space() << "capabilities:" << t.capabilities();
    return d;
}

McpProtocolInitializeResult McpProtocolInitializeResult::fromJson(const QJsonObject &obj)
{
    McpProtocolInitializeResult result;
    if (!obj.contains("capabilities"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: capabilities";
        return {};
    }
    if (!obj.contains("protocolVersion"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: protocolVersion";
        return {};
    }
    if (!obj.contains("serverInfo"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: serverInfo";
        return {};
    }
    if (const QJsonValue capabilitiesValue = obj.value("capabilities"_L1); capabilitiesValue.isObject()) {
        result.setCapabilities(McpProtocolServerCapabilities::fromJson(capabilitiesValue.toObject()));
    }
    if (obj.contains("instructions"_L1)) {
        result.setInstructions(obj.value("instructions"_L1).toString());
    }
    result.setProtocolVersion(obj["protocolVersion"_L1].toString());
    if (const QJsonValue serverInfoValue = obj.value("serverInfo"_L1); serverInfoValue.isObject()) {
        result.setServerInfo(McpProtocolImplementation::fromJson(serverInfoValue.toObject()));
    }

    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        result.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    return result;
}

QJsonObject McpProtocolInitializeResult::toJson(const McpProtocolInitializeResult &result)
{
    QJsonObject obj;
    obj["capabilities"_L1] = McpProtocolServerCapabilities::toJson(result.capabilities());
    obj["protocolVersion"_L1] = result.protocolVersion();
    obj["serverInfo"_L1] = McpProtocolImplementation::toJson(result.serverInfo());

    if (result.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*result.meta());
    }
    if (result.instructions().has_value()) {
        obj["instructions"_L1] = *result.instructions();
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

void McpProtocolInitializeResult::setServerInfo(McpProtocolImplementation newServerInfo)
{
    mServerInfo = std::move(newServerInfo);
}

McpProtocolServerCapabilities McpProtocolInitializeResult::capabilities() const
{
    return mCapabilities;
}

void McpProtocolInitializeResult::setCapabilities(McpProtocolServerCapabilities newCapabilities)
{
    mCapabilities = std::move(newCapabilities);
}
