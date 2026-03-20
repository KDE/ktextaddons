/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocollistresourcesresult.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolListResourcesResult::McpProtocolListResourcesResult() = default;

McpProtocolListResourcesResult::~McpProtocolListResourcesResult() = default;

bool McpProtocolListResourcesResult::operator==(const McpProtocolListResourcesResult &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolListResourcesResult &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "nextCursor:" << t.nextCursor();
    return d;
}

McpProtocolListResourcesResult McpProtocolListResourcesResult::fromJson(const QJsonObject &obj)
{
    McpProtocolListResourcesResult prompt;
    // TODO
    return prompt;
}

QJsonObject McpProtocolListResourcesResult::toJson(const McpProtocolListResourcesResult &boolean)
{
    QJsonObject obj;
    // TODO
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolListResourcesResult::meta() const
{
    return mMeta;
}

void McpProtocolListResourcesResult::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = newMeta;
}

std::optional<QString> McpProtocolListResourcesResult::nextCursor() const
{
    return mNextCursor;
}

void McpProtocolListResourcesResult::setNextCursor(std::optional<QString> newNextCursor)
{
    mNextCursor = newNextCursor;
}
