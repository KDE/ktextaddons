/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolunsubscriberequestparams.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolUnsubscribeRequestParams::McpProtocolUnsubscribeRequestParams() = default;

McpProtocolUnsubscribeRequestParams::~McpProtocolUnsubscribeRequestParams() = default;

bool McpProtocolUnsubscribeRequestParams::operator==(const McpProtocolUnsubscribeRequestParams &other) const = default;
bool McpProtocolUnsubscribeRequestParams::Meta::operator==(const McpProtocolUnsubscribeRequestParams::Meta &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolUnsubscribeRequestParams &t)
{
    return d;
}

McpProtocolUnsubscribeRequestParams::Meta McpProtocolUnsubscribeRequestParams::Meta::fromJson(const QJsonObject &obj)
{
    McpProtocolUnsubscribeRequestParams::Meta meta;
    if (obj.contains("progressToken"_L1)) {
        meta.setProgressToken(McpProtocolUtils::progressTokenFromJson(obj["progressToken"_L1].toObject()));
    }
    return meta;
}

QJsonObject McpProtocolUnsubscribeRequestParams::Meta::toJson(const McpProtocolUnsubscribeRequestParams::Meta &image)
{
    QJsonObject obj;
    if (image.progressToken().has_value()) {
        obj["progressToken"_L1] = McpProtocolUtils::progressTokenToJson(*image.progressToken());
    }
    return obj;
}

McpProtocolUnsubscribeRequestParams McpProtocolUnsubscribeRequestParams::fromJson(const QJsonObject &obj)
{
    McpProtocolUnsubscribeRequestParams prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolUnsubscribeRequestParams::Meta::fromJson(obj["_meta"_L1].toObject()));
    }
    prompt.setUri(obj.value("uri"_L1).toString());
    return prompt;
}

QJsonObject McpProtocolUnsubscribeRequestParams::toJson(const McpProtocolUnsubscribeRequestParams &boolean)
{
    QJsonObject obj;
    obj["uri"_L1] = boolean.uri();
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolUnsubscribeRequestParams::Meta::toJson(*boolean.meta());
    }
    return obj;
}

std::optional<McpProtocolUnsubscribeRequestParams::Meta> McpProtocolUnsubscribeRequestParams::meta() const
{
    return mMeta;
}

void McpProtocolUnsubscribeRequestParams::setMeta(std::optional<Meta> newMeta)
{
    mMeta = std::move(newMeta);
}

QString McpProtocolUnsubscribeRequestParams::uri() const
{
    return mUri;
}

void McpProtocolUnsubscribeRequestParams::setUri(const QString &newUri)
{
    mUri = newUri;
}

std::optional<McpProtocolUtils::ProgressToken> McpProtocolUnsubscribeRequestParams::Meta::progressToken() const
{
    return mProgressToken;
}

void McpProtocolUnsubscribeRequestParams::Meta::setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken)
{
    mProgressToken = std::move(newProgressToken);
}
