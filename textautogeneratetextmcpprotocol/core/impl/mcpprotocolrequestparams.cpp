/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolrequestparams.h"
#include <QDebug>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolRequestParams::McpProtocolRequestParams() = default;

bool McpProtocolRequestParams::operator==(const McpProtocolRequestParams &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolRequestParams &t)
{
    d.space() << "meta:" << t.meta();
    return d;
}

McpProtocolRequestParams McpProtocolRequestParams::fromJson(const QJsonObject &obj)
{
    McpProtocolRequestParams prompt;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        prompt.setMeta(McpProtocolRequestParams::Meta::fromJson(metaValue.toObject()));
    }
    return prompt;
}

QJsonObject McpProtocolRequestParams::toJson(const McpProtocolRequestParams &requestParams)
{
    QJsonObject obj;
    if (requestParams.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolRequestParams::Meta::toJson(*requestParams.meta());
    }
    return obj;
}

std::optional<McpProtocolRequestParams::Meta> McpProtocolRequestParams::meta() const
{
    return mMeta;
}

void McpProtocolRequestParams::setMeta(std::optional<Meta> newMeta)
{
    mMeta = std::move(newMeta);
}
