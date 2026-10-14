/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolunsubscriberequestparams.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolUnsubscribeRequestParams::McpProtocolUnsubscribeRequestParams() = default;

bool McpProtocolUnsubscribeRequestParams::operator==(const McpProtocolUnsubscribeRequestParams &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolUnsubscribeRequestParams &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "uri:" << t.uri();
    return d;
}

McpProtocolUnsubscribeRequestParams McpProtocolUnsubscribeRequestParams::fromJson(const QJsonObject &obj)
{
    McpProtocolUnsubscribeRequestParams prompt;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        prompt.setMeta(McpProtocolUnsubscribeRequestParams::Meta::fromJson(metaValue.toObject()));
    }
    if (const QJsonValue uriValue = obj.value("uri"_L1); uriValue.isString()) {
        prompt.setUri(uriValue.toString());
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolUnsubscribeRequestParams: missing required field 'uri'";
        return {};
    }
    return prompt;
}

bool McpProtocolUnsubscribeRequestParams::isValid() const
{
    return !mUri.isEmpty();
}

QJsonObject McpProtocolUnsubscribeRequestParams::toJson(const McpProtocolUnsubscribeRequestParams &unsubscribeRequestParams)
{
    QJsonObject obj;
    obj["uri"_L1] = unsubscribeRequestParams.uri();
    if (unsubscribeRequestParams.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolUnsubscribeRequestParams::Meta::toJson(*unsubscribeRequestParams.meta());
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
