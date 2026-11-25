/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolsubscriptionslistenresult.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolSubscriptionsListenResult::McpProtocolSubscriptionsListenResult() = default;

bool McpProtocolSubscriptionsListenResult::operator==(const McpProtocolSubscriptionsListenResult &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolSubscriptionsListenResult &t)
{
    d.space() << "meta:" << t.meta();
    return d;
}

McpProtocolSubscriptionsListenResult McpProtocolSubscriptionsListenResult::fromJson(const QJsonObject &obj)
{
    McpProtocolSubscriptionsListenResult result;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        McpProtocolSubscriptionsListenResultMetaObject meta = McpProtocolSubscriptionsListenResultMetaObject::fromJson(metaValue.toObject());
        if (!meta.isValid()) {
            qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolSubscriptionsListenResult: invalid field '_meta'";
            return {};
        }
        result.setMeta(std::move(meta));
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolSubscriptionsListenResult: missing required field '_meta'";
        return {};
    }
    return result;
}

bool McpProtocolSubscriptionsListenResult::isValid() const
{
    return mMeta.isValid();
}

QJsonObject McpProtocolSubscriptionsListenResult::toJson(const McpProtocolSubscriptionsListenResult &result)
{
    QJsonObject obj;
    obj["_meta"_L1] = McpProtocolSubscriptionsListenResultMetaObject::toJson(result.meta());
    return obj;
}

McpProtocolSubscriptionsListenResultMetaObject McpProtocolSubscriptionsListenResult::meta() const
{
    return mMeta;
}

void McpProtocolSubscriptionsListenResult::setMeta(McpProtocolSubscriptionsListenResultMetaObject newMeta)
{
    mMeta = std::move(newMeta);
}
