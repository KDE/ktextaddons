/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolerror.h"
#include <QJsonObject>

#include <QDebug>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolError::McpProtocolError() = default;

McpProtocolError::~McpProtocolError() = default;

bool McpProtocolError::operator==(const McpProtocolError &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolError &t)
{
    d.space() << "code:" << t.code();
    d.space() << "data:" << t.data();
    d.space() << "message:" << t.message();
    return d;
}

McpProtocolError McpProtocolError::fromJson(const QJsonObject &obj)
{
    McpProtocolError error;
    error.setCode(obj.value("code"_L1).toInt());
    if (obj.contains("data"_L1)) {
        error.setData(obj["data"_L1].toString());
    }
    error.setMessage(obj["message"_L1].toString());
    return error;
}

QJsonObject McpProtocolError::toJson(const McpProtocolError &error)
{
    QJsonObject obj;
    obj["code"_L1] = error.code();
    obj["message"_L1] = error.message();
    if (error.data().has_value()) {
        obj["data"_L1] = *error.data();
    }
    return obj;
}

int McpProtocolError::code() const
{
    return mCode;
}

void McpProtocolError::setCode(int newCode)
{
    mCode = newCode;
}

std::optional<QString> McpProtocolError::data() const
{
    return mData;
}

void McpProtocolError::setData(std::optional<QString> newData)
{
    mData = std::move(newData);
}

QString McpProtocolError::message() const
{
    return mMessage;
}

void McpProtocolError::setMessage(const QString &newMessage)
{
    mMessage = newMessage;
}

#include "moc_mcpprotocolerror.cpp"
