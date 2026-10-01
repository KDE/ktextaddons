/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolinitializerequestparams.h"
#include <QDebug>
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolInitializeRequestParams::McpProtocolInitializeRequestParams() = default;

bool McpProtocolInitializeRequestParams::operator==(const McpProtocolInitializeRequestParams &other) const = default;
bool McpProtocolInitializeRequestParams::Meta::operator==(const McpProtocolInitializeRequestParams::Meta &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeRequestParams &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "clientInfo:" << t.clientInfo();
    d.space() << "protocolVersion:" << t.protocolVersion();
    d.space() << "capabilities:" << t.capabilities();
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeRequestParams::Meta &t)
{
    d.space() << "progressToken:" << t.progressToken();
    return d;
}

McpProtocolInitializeRequestParams::Meta McpProtocolInitializeRequestParams::Meta::fromJson(const QJsonObject &obj)
{
    McpProtocolInitializeRequestParams::Meta meta;
    if (obj.contains("progressToken"_L1)) {
        meta.setProgressToken(McpProtocolUtils::progressTokenFromJson(obj["progressToken"_L1]));
    }
    return meta;
}

QJsonObject McpProtocolInitializeRequestParams::Meta::toJson(const McpProtocolInitializeRequestParams::Meta &meta)
{
    QJsonObject obj;
    if (meta.progressToken().has_value()) {
        obj["progressToken"_L1] = McpProtocolUtils::progressTokenToJson(*meta.progressToken());
    }
    return obj;
}

McpProtocolInitializeRequestParams McpProtocolInitializeRequestParams::fromJson(const QJsonObject &obj)
{
    McpProtocolInitializeRequestParams params;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        params.setMeta(McpProtocolInitializeRequestParams::Meta::fromJson(metaValue.toObject()));
    }
    if (const QJsonValue capabilitiesValue = obj.value("capabilities"_L1); capabilitiesValue.isObject()) {
        params.setCapabilities(McpProtocolClientCapabilities::fromJson(capabilitiesValue.toObject()));
    }
    if (const QJsonValue clientInfoValue = obj.value("clientInfo"_L1); clientInfoValue.isObject()) {
        params.setClientInfo(McpProtocolImplementation::fromJson(clientInfoValue.toObject()));
    }
    params.setProtocolVersion(obj.value("protocolVersion"_L1).toString());
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

std::optional<McpProtocolUtils::ProgressToken> McpProtocolInitializeRequestParams::Meta::progressToken() const
{
    return mProgressToken;
}

void McpProtocolInitializeRequestParams::Meta::setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken)
{
    mProgressToken = std::move(newProgressToken);
}
