/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolprogressnotificationparams.h"
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolProgressNotificationParams::McpProtocolProgressNotificationParams() = default;

McpProtocolProgressNotificationParams::~McpProtocolProgressNotificationParams() = default;

bool McpProtocolProgressNotificationParams::operator==(const McpProtocolProgressNotificationParams &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolProgressNotificationParams &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "message:" << t.message();
    d.space() << "progress:" << t.progress();
    d.space() << "progressToken:" << t.progressToken();
    d.space() << "total:" << t.total();
    return d;
}

McpProtocolProgressNotificationParams McpProtocolProgressNotificationParams::fromJson(const QJsonObject &obj)
{
    McpProtocolProgressNotificationParams prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(obj["_meta"_L1].toObject()));
    }
    if (obj.contains("message"_L1)) {
        prompt.setMessage(obj.value("message"_L1).toString());
    }
    prompt.setProgress(obj.value("progress"_L1).toDouble());
    if (obj.contains("progressToken"_L1)) {
        prompt.setProgressToken(McpProtocolUtils::progressTokenFromJson(obj["progressToken"_L1].toObject()));
    }
    if (obj.contains("total"_L1)) {
        prompt.setTotal(obj.value("total"_L1).toDouble());
    }
    return prompt;
}

QJsonObject McpProtocolProgressNotificationParams::toJson(const McpProtocolProgressNotificationParams &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }
    obj["progress"_L1] = boolean.progress();
    obj["progressToken"_L1] = McpProtocolUtils::progressTokenToJson(boolean.progressToken());

    if (boolean.message().has_value()) {
        obj.insert("message"_L1, *boolean.message());
    }
    if (boolean.total().has_value()) {
        obj.insert("total"_L1, *boolean.total());
    }
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolProgressNotificationParams::meta() const
{
    return mMeta;
}

void McpProtocolProgressNotificationParams::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

std::optional<QString> McpProtocolProgressNotificationParams::message() const
{
    return mMessage;
}

void McpProtocolProgressNotificationParams::setMessage(std::optional<QString> newMessage)
{
    mMessage = std::move(newMessage);
}

double McpProtocolProgressNotificationParams::progress() const
{
    return mProgress;
}

void McpProtocolProgressNotificationParams::setProgress(double newProgress)
{
    mProgress = newProgress;
}

McpProtocolUtils::ProgressToken McpProtocolProgressNotificationParams::progressToken() const
{
    return mProgressToken;
}

void McpProtocolProgressNotificationParams::setProgressToken(const McpProtocolUtils::ProgressToken &newProgressToken)
{
    mProgressToken = newProgressToken;
}

std::optional<double> McpProtocolProgressNotificationParams::total() const
{
    return mTotal;
}

void McpProtocolProgressNotificationParams::setTotal(std::optional<double> newTotal)
{
    mTotal = newTotal;
}
