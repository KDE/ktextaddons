/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolcompleterequestparams.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolCompleteRequestParams::McpProtocolCompleteRequestParams() = default;

McpProtocolCompleteRequestParams::~McpProtocolCompleteRequestParams() = default;

bool McpProtocolCompleteRequestParams::operator==(const McpProtocolCompleteRequestParams &other) const = default;
bool McpProtocolCompleteRequestParams::Meta::operator==(const McpProtocolCompleteRequestParams::Meta &other) const = default;
bool McpProtocolCompleteRequestParams::Context::operator==(const McpProtocolCompleteRequestParams::Context &other) const = default;
bool McpProtocolCompleteRequestParams::Argument::operator==(const McpProtocolCompleteRequestParams::Argument &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolCompleteRequestParams &t)
{
    return d;
}

McpProtocolCompleteRequestParams::Meta McpProtocolCompleteRequestParams::Meta::fromJson(const QJsonObject &obj)
{
    return {};
}

QJsonObject McpProtocolCompleteRequestParams::Meta::toJson(const McpProtocolCompleteRequestParams::Meta &image)
{
    QJsonObject obj;
#if 0
    if (image.progressToken().has_value()) {
        obj.insert("progressToken", McpProtocolUtils::toJson(*image.progressToken()));
    }
#endif
    return obj;
}

McpProtocolCompleteRequestParams McpProtocolCompleteRequestParams::fromJson(const QJsonObject &obj)
{
    McpProtocolCompleteRequestParams prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolCompleteRequestParams::Meta::fromJson(obj["_meta"_L1].toObject()));
    }
    return prompt;
}

QJsonObject McpProtocolCompleteRequestParams::toJson(const McpProtocolCompleteRequestParams &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolCompleteRequestParams::Meta::toJson(*boolean.meta());
    }
    return obj;
}

std::optional<McpProtocolCompleteRequestParams::Meta> McpProtocolCompleteRequestParams::meta() const
{
    return mMeta;
}

void McpProtocolCompleteRequestParams::setMeta(std::optional<Meta> newMeta)
{
    mMeta = std::move(newMeta);
}

std::optional<McpProtocolUtils::ProgressToken> McpProtocolCompleteRequestParams::Meta::progressToken() const
{
    return mProgressToken;
}

void McpProtocolCompleteRequestParams::Meta::setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken)
{
    mProgressToken = std::move(newProgressToken);
}
