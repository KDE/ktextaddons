/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolsubscriberequestparams.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolSubscribeRequestParams::McpProtocolSubscribeRequestParams() = default;

bool McpProtocolSubscribeRequestParams::operator==(const McpProtocolSubscribeRequestParams &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolSubscribeRequestParams &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "uri:" << t.uri();
    return d;
}

McpProtocolSubscribeRequestParams McpProtocolSubscribeRequestParams::fromJson(const QJsonObject &obj)
{
    McpProtocolSubscribeRequestParams prompt;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        prompt.setMeta(McpProtocolSubscribeRequestParams::Meta::fromJson(metaValue.toObject()));
    }
    if (const QJsonValue uriValue = obj.value("uri"_L1); uriValue.isString()) {
        prompt.setUri(uriValue.toString());
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolSubscribeRequestParams: missing required field 'uri'";
        return {};
    }
    return prompt;
}

bool McpProtocolSubscribeRequestParams::isValid() const
{
    return !mUri.isEmpty();
}

QJsonObject McpProtocolSubscribeRequestParams::toJson(const McpProtocolSubscribeRequestParams &subscribeRequestParams)
{
    QJsonObject obj;
    obj["uri"_L1] = subscribeRequestParams.uri();
    if (subscribeRequestParams.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolSubscribeRequestParams::Meta::toJson(*subscribeRequestParams.meta());
    }
    return obj;
}

std::optional<McpProtocolSubscribeRequestParams::Meta> McpProtocolSubscribeRequestParams::meta() const
{
    return mMeta;
}

void McpProtocolSubscribeRequestParams::setMeta(std::optional<Meta> newMeta)
{
    mMeta = std::move(newMeta);
}

QString McpProtocolSubscribeRequestParams::uri() const
{
    return mUri;
}

void McpProtocolSubscribeRequestParams::setUri(const QString &newUri)
{
    mUri = newUri;
}
