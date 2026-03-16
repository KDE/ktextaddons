/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoltoolusecontent.h"
#include <QDebug>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolToolUseContent::McpProtocolToolUseContent() = default;

McpProtocolToolUseContent::~McpProtocolToolUseContent() = default;

QByteArray McpProtocolToolUseContent::type()
{
    return QByteArrayLiteral("tool_use");
}

bool McpProtocolToolUseContent::operator==(const McpProtocolToolUseContent &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolToolUseContent &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "name:" << t.name();
    return d;
}

QJsonObject McpProtocolToolUseContent::meta() const
{
    return mMeta;
}

void McpProtocolToolUseContent::setMeta(const QJsonObject &newMeta)
{
    mMeta = newMeta;
}

McpProtocolToolUseContent McpProtocolToolUseContent::fromJson(const QJsonObject &obj)
{
    McpProtocolToolUseContent text;
    if (obj.value("type"_L1).toString() != QString::fromLatin1(McpProtocolToolUseContent::type())) {
        qWarning() << "McpProtocolToolUseContent: type is not correct " << obj.value("type"_L1).toString();
        return {};
    }

    if (obj.contains("_meta"_L1)) {
        text.setMeta(obj["_meta"_L1].toObject());
    }
    return text;
}

QJsonObject McpProtocolToolUseContent::toJson(const McpProtocolToolUseContent &text)
{
    return {};
}

QString McpProtocolToolUseContent::name() const
{
    return mName;
}

void McpProtocolToolUseContent::setName(const QString &newName)
{
    mName = newName;
}
