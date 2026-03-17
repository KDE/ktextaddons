/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoltoolchoice.h"
#include <QDebug>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolToolChoice::McpProtocolToolChoice() = default;

McpProtocolToolChoice::~McpProtocolToolChoice() = default;

bool McpProtocolToolChoice::operator==(const McpProtocolToolChoice &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolToolChoice &t)
{
    d.space() << "mode:" << t.mode();
    return d;
}

McpProtocolToolChoice McpProtocolToolChoice::fromJson(const QJsonObject &obj)
{
    return {};
}

QJsonObject McpProtocolToolChoice::toJson(const McpProtocolToolChoice &choice)
{
    QJsonObject obj;
    if (choice.mode() != McpProtocolToolChoice::Mode::Unknown) {
        // obj.insert("mode", toJsonValue(*data._mode));
    }
    return obj;
}

McpProtocolToolChoice::Mode McpProtocolToolChoice::mode() const
{
    return mMode;
}

void McpProtocolToolChoice::setMode(Mode newMode)
{
    mMode = newMode;
}
