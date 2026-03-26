/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoltextcontent.h"
#include "textautogeneratetextmcpprotocol_debug.h"
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolTextContent::McpProtocolTextContent() = default;

McpProtocolTextContent::~McpProtocolTextContent() = default;

QByteArray McpProtocolTextContent::type()
{
    return QByteArrayLiteral("text");
}

bool McpProtocolTextContent::operator==(const McpProtocolTextContent &other) const = default;

QString McpProtocolTextContent::text() const
{
    return mText;
}

void McpProtocolTextContent::setText(const QString &newText)
{
    mText = newText;
}

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolTextContent &t)
{
    d.space() << "text:" << t.text();
    d.space() << "annotations:" << t.annotations();
    d.space() << "meta:" << t.meta();
    return d;
}

std::optional<McpProtocolAnnotations> McpProtocolTextContent::annotations() const
{
    return mAnnotations;
}

void McpProtocolTextContent::setAnnotations(std::optional<McpProtocolAnnotations> newAnnotations)
{
    mAnnotations = std::move(newAnnotations);
}

McpProtocolTextContent McpProtocolTextContent::fromJson(const QJsonObject &obj)
{
    McpProtocolTextContent text;
    if (obj.value("type"_L1).toString() != QString::fromLatin1(McpProtocolTextContent::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "McpProtocolTextContent: type is not correct " << obj.value("type"_L1).toString();
        return {};
    }

    text.setText(obj["text"_L1].toString());
    if (obj.contains("annotations"_L1)) {
        text.setAnnotations(McpProtocolAnnotations::fromJson(obj["annotations"_L1].toObject()));
    }
    if (obj.contains("_meta"_L1)) {
        text.setMeta(McpProtocolMeta::fromJson(obj["_meta"_L1].toObject()));
    }
    return text;
}

QJsonObject McpProtocolTextContent::toJson(const McpProtocolTextContent &text)
{
    QJsonObject obj;
    obj["type"_L1] = QString::fromLatin1(text.type());
    if (text.annotations().has_value()) {
        obj["annotations"_L1] = McpProtocolAnnotations::toJson(*text.annotations());
    }
    obj["text"_L1] = text.text();
    if (text.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*text.meta());
    }
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolTextContent::meta() const
{
    return mMeta;
}

void McpProtocolTextContent::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}
