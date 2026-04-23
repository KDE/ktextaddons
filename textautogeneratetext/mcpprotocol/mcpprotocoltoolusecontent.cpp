/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoltoolusecontent.h"
#include <QDebug>
#include <QJsonObject>
#include <utility>
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
    d.space() << "id:" << t.id();
    d.space() << "input:" << t.input();
    return d;
}

McpProtocolToolUseContent McpProtocolToolUseContent::fromJson(const QJsonObject &obj)
{
    McpProtocolToolUseContent tool;
    if (obj.value("type"_L1).toString() != QString::fromLatin1(McpProtocolToolUseContent::type())) {
        qWarning() << "McpProtocolToolUseContent: type is not correct " << obj.value("type"_L1).toString();
        return {};
    }

    if (obj.contains("_meta"_L1)) {
        tool.setMeta(McpProtocolMeta::fromJson(obj["_meta"_L1].toObject()));
    }
    tool.setId(obj["id"_L1].toString());
    tool.setName(obj.value("name"_L1).toString());

    if (obj.contains("input"_L1) && obj["input"_L1].isObject()) {
        const QJsonObject mapObj_input = obj["input"_L1].toObject();
        QMap<QString, QJsonValue> map_input;
        for (auto it = mapObj_input.constBegin(); it != mapObj_input.constEnd(); ++it) {
            map_input.insert(it.key(), it.value());
        }
        tool.setInput(map_input);
    }
    return tool;
}

QJsonObject McpProtocolToolUseContent::toJson(const McpProtocolToolUseContent &tool)
{
    QJsonObject obj;
    obj["id"_L1] = tool.id();
    obj["name"_L1] = tool.name();
    obj["type"_L1] = QString::fromLatin1(McpProtocolToolUseContent::type());
    if (tool.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*tool.meta());
    }

    QJsonObject map_input;
    for (auto it = tool.input().constBegin(); it != tool.input().constEnd(); ++it) {
        map_input.insert(it.key(), it.value());
    }
    obj["input"_L1] = map_input;
    return obj;
}

QString McpProtocolToolUseContent::name() const
{
    return mName;
}

void McpProtocolToolUseContent::setName(const QString &newName)
{
    mName = newName;
}

QString McpProtocolToolUseContent::id() const
{
    return mId;
}

void McpProtocolToolUseContent::setId(const QString &newId)
{
    mId = newId;
}

QMap<QString, QJsonValue> McpProtocolToolUseContent::input() const
{
    return mInput;
}

void McpProtocolToolUseContent::setInput(const QMap<QString, QJsonValue> &newInput)
{
    mInput = newInput;
}

std::optional<McpProtocolMeta> McpProtocolToolUseContent::meta() const
{
    return mMeta;
}

void McpProtocolToolUseContent::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}
