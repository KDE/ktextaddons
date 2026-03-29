/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolinitializerequestparams.h"
#include <QDebug>
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolInitializeRequestParams::McpProtocolInitializeRequestParams() = default;

McpProtocolInitializeRequestParams::~McpProtocolInitializeRequestParams() = default;

bool McpProtocolInitializeRequestParams::operator==(const McpProtocolInitializeRequestParams &other) const = default;
bool McpProtocolInitializeRequestParams::Meta::operator==(const McpProtocolInitializeRequestParams::Meta &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolInitializeRequestParams &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "clientInfo:" << t.clientInfo();
    d.space() << "protocolVersion:" << t.protocolVersion();
    d.space() << "capabilities:" << t.capabilities();
    return d;
}

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolInitializeRequestParams::Meta &t)
{
    d.space() << "progressToken:" << t.progressToken();
    return d;
}

McpProtocolInitializeRequestParams::Meta McpProtocolInitializeRequestParams::Meta::fromJson(const QJsonObject &obj)
{
    McpProtocolInitializeRequestParams::Meta meta;
    if (obj.contains("progressToken"_L1)) {
        meta.setProgressToken(McpProtocolUtils::progressTokenFromJson(obj["progressToken"_L1].toObject()));
    }
    return meta;
}

QJsonObject McpProtocolInitializeRequestParams::Meta::toJson(const McpProtocolInitializeRequestParams::Meta &image)
{
    QJsonObject obj;
    if (image.progressToken().has_value()) {
        obj["progressToken"_L1] = McpProtocolUtils::progressTokenToJson(*image.progressToken());
    }
    return obj;
}

McpProtocolInitializeRequestParams McpProtocolInitializeRequestParams::fromJson(const QJsonObject &obj)
{
    McpProtocolInitializeRequestParams prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolInitializeRequestParams::Meta::fromJson(obj["_meta"_L1].toObject()));
    }
    if (obj.contains("capabilities"_L1) && obj["capabilities"_L1].isObject()) {
        prompt.setCapabilities(McpProtocolClientCapabilities::fromJson(obj["capabilities"_L1].toObject()));
    }
    if (obj.contains("clientInfo"_L1) && obj["clientInfo"_L1].isObject()) {
        prompt.setClientInfo(McpProtocolImplementation::fromJson(obj["clientInfo"_L1].toObject()));
    }
    prompt.setProtocolVersion(obj.value("protocolVersion"_L1).toString());
    return prompt;
}

QJsonObject McpProtocolInitializeRequestParams::toJson(const McpProtocolInitializeRequestParams &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolInitializeRequestParams::Meta::toJson(*boolean.meta());
    }
    obj["capabilities"_L1] = McpProtocolClientCapabilities::toJson(boolean.capabilities());
    obj["clientInfo"_L1] = McpProtocolImplementation::toJson(boolean.clientInfo());
    obj["protocolVersion"_L1] = boolean.protocolVersion();
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

void McpProtocolInitializeRequestParams::setClientInfo(const McpProtocolImplementation &newClientInfo)
{
    mClientInfo = newClientInfo;
}

McpProtocolClientCapabilities McpProtocolInitializeRequestParams::capabilities() const
{
    return mCapabilities;
}

void McpProtocolInitializeRequestParams::setCapabilities(const McpProtocolClientCapabilities &newCapabilities)
{
    mCapabilities = newCapabilities;
}

std::optional<McpProtocolUtils::ProgressToken> McpProtocolInitializeRequestParams::Meta::progressToken() const
{
    return mProgressToken;
}

void McpProtocolInitializeRequestParams::Meta::setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken)
{
    mProgressToken = std::move(newProgressToken);
}
