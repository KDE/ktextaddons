/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoltask.h"
#include <QDebug>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolTask::McpProtocolTask() = default;

McpProtocolTask::~McpProtocolTask() = default;

QByteArray McpProtocolTask::type()
{
    return QByteArrayLiteral("text");
}

bool McpProtocolTask::operator==(const McpProtocolTask &other) const = default;

QString McpProtocolTask::text() const
{
    return mText;
}

void McpProtocolTask::setText(const QString &newText)
{
    mText = newText;
}

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolTask &t)
{
    d.space() << "text:" << t.text();
    d.space() << "annotations:" << t.annotations();
    d.space() << "meta:" << t.meta();
    return d;
}

std::optional<McpProtocolAnnotations> McpProtocolTask::annotations() const
{
    return mAnnotations;
}

void McpProtocolTask::setAnnotations(std::optional<McpProtocolAnnotations> newAnnotations)
{
    mAnnotations = std::move(newAnnotations);
}

QJsonObject McpProtocolTask::meta() const
{
    return mMeta;
}

void McpProtocolTask::setMeta(const QJsonObject &newMeta)
{
    mMeta = newMeta;
}

McpProtocolTask McpProtocolTask::fromJson(const QJsonObject &obj)
{
    McpProtocolTask text;
    if (obj.value("type"_L1).toString() != QString::fromLatin1(McpProtocolTask::type())) {
        qWarning() << "McpProtocolTask: type is not correct " << obj.value("type"_L1).toString();
        return {};
    }

    text.setText(obj["text"_L1].toString());
    if (obj.contains("annotations"_L1)) {
        text.setAnnotations(McpProtocolAnnotations::fromJson(obj["annotations"_L1].toObject()));
    }
    if (obj.contains("_meta"_L1)) {
        text.setMeta(obj["_meta"_L1].toObject());
    }
    return text;
}

QJsonObject McpProtocolTask::toJson(const McpProtocolTask &text)
{
    return {};
}
