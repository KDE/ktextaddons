/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolinitializerequestparams.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolInitializeRequestParams::McpProtocolInitializeRequestParams() = default;

bool McpProtocolInitializeRequestParams::operator==(const McpProtocolInitializeRequestParams &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeRequestParams &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "clientInfo:" << t.clientInfo();
    d.space() << "protocolVersion:" << t.protocolVersion();
    d.space() << "capabilities:" << t.capabilities();
    return d;
}

bool McpProtocolInitializeRequestParams::isValid() const
{
    return !mProtocolVersion.isEmpty() && mClientInfo.isValid();
}

McpProtocolInitializeRequestParams McpProtocolInitializeRequestParams::fromJson(const QJsonObject &obj)
{
    McpProtocolInitializeRequestParams params;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        params.setMeta(McpProtocolInitializeRequestParams::Meta::fromJson(metaValue.toObject()));
    }
    if (const QJsonValue capabilitiesValue = obj.value("capabilities"_L1); capabilitiesValue.isObject()) {
        params.setCapabilities(McpProtocolClientCapabilities::fromJson(capabilitiesValue.toObject()));
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolInitializeRequestParams: missing required field 'capabilities'";
        return {};
    }
    if (const QJsonValue clientInfoValue = obj.value("clientInfo"_L1); clientInfoValue.isObject()) {
        const McpProtocolImplementation clientInfo = McpProtocolImplementation::fromJson(clientInfoValue.toObject());
        if (!clientInfo.isValid()) {
            qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolInitializeRequestParams: invalid field 'clientInfo'";
            return {};
        }
        params.setClientInfo(clientInfo);
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolInitializeRequestParams: missing required field 'clientInfo'";
        return {};
    }
    if (const QJsonValue protocolVersionValue = obj.value("protocolVersion"_L1); protocolVersionValue.isString()) {
        params.setProtocolVersion(protocolVersionValue.toString());
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolInitializeRequestParams: missing required field 'protocolVersion'";
        return {};
    }
    return params;
}

QJsonObject McpProtocolInitializeRequestParams::toJson(const McpProtocolInitializeRequestParams &params)
{
    QJsonObject obj;
    if (params.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolInitializeRequestParams::Meta::toJson(*params.meta());
    }
    obj["capabilities"_L1] = McpProtocolClientCapabilities::toJson(params.capabilities());
    obj["clientInfo"_L1] = McpProtocolImplementation::toJson(params.clientInfo());
    obj["protocolVersion"_L1] = params.protocolVersion();
    return obj;
}

std::optional<McpProtocolInitializeRequestParams::Meta> McpProtocolInitializeRequestParams::meta() const
{
    return mMeta;
}

void McpProtocolInitializeRequestParams::setMeta(std::optional<Meta> newMeta)
{
    mMeta = std::move(newMeta);
}

QString McpProtocolInitializeRequestParams::protocolVersion() const
{
    return mProtocolVersion;
}

void McpProtocolInitializeRequestParams::setProtocolVersion(const QString &newProtocolVersion)
{
    mProtocolVersion = newProtocolVersion;
}

McpProtocolImplementation McpProtocolInitializeRequestParams::clientInfo() const
{
    return mClientInfo;
}

void McpProtocolInitializeRequestParams::setClientInfo(McpProtocolImplementation newClientInfo)
{
    mClientInfo = std::move(newClientInfo);
}

McpProtocolClientCapabilities McpProtocolInitializeRequestParams::capabilities() const
{
    return mCapabilities;
}

void McpProtocolInitializeRequestParams::setCapabilities(McpProtocolClientCapabilities newCapabilities)
{
    mCapabilities = std::move(newCapabilities);
}
