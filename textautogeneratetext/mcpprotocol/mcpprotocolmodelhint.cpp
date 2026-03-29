/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolmodelhint.h"
#include <QDebug>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolModelHint::McpProtocolModelHint() = default;

McpProtocolModelHint::~McpProtocolModelHint() = default;

bool McpProtocolModelHint::operator==(const McpProtocolModelHint &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolModelHint &t)
{
    d.space() << "name:" << t.name();
    return d;
}

McpProtocolModelHint McpProtocolModelHint::fromJson(const QJsonObject &obj)
{
    McpProtocolModelHint modelHint;
    if (obj.contains("name"_L1)) {
        modelHint.setName(obj.value("name"_L1).toString());
    }
    return modelHint;
}

QJsonObject McpProtocolModelHint::toJson(const McpProtocolModelHint &choice)
{
    QJsonObject obj;
    if (choice.name().has_value()) {
        obj["name"_L1] = *choice.name();
    }
    return obj;
}

std::optional<QString> McpProtocolModelHint::name() const
{
    return mName;
}

void McpProtocolModelHint::setName(std::optional<QString> newName)
{
    mName = std::move(newName);
}

#include "moc_mcpprotocolmodelhint.cpp"
