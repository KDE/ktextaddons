/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolprogressnotificationparams.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolProgressNotificationParams::McpProtocolProgressNotificationParams() = default;

bool McpProtocolProgressNotificationParams::operator==(const McpProtocolProgressNotificationParams &other) const = default;

bool McpProtocolProgressNotificationParams::isValid() const
{
    if (const auto *token = std::get_if<QString>(&mProgressToken)) {
        return !token->isEmpty();
    }
    return true;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolProgressNotificationParams &t)
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
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    if (obj.contains("message"_L1)) {
        prompt.setMessage(obj.value("message"_L1).toString());
    }
    if (const QJsonValue progressValue = obj.value("progress"_L1); progressValue.isDouble()) {
        prompt.setProgress(progressValue.toDouble());
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolProgressNotificationParams: missing required field 'progress'";
        return {};
    }
    if (const QJsonValue progressTokenValue = obj.value("progressToken"_L1); progressTokenValue.isString() || progressTokenValue.isDouble()) {
        prompt.setProgressToken(McpProtocolUtils::progressTokenFromJson(progressTokenValue));
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolProgressNotificationParams: missing required field 'progressToken'";
        return {};
    }
    if (const QJsonValue totalValue = obj.value("total"_L1); totalValue.isDouble()) {
        prompt.setTotal(totalValue.toDouble());
    }
    return prompt;
}

QJsonObject McpProtocolProgressNotificationParams::toJson(const McpProtocolProgressNotificationParams &progressNotificationParams)
{
    QJsonObject obj;
    if (progressNotificationParams.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*progressNotificationParams.meta());
    }
    obj["progress"_L1] = progressNotificationParams.progress();
    obj["progressToken"_L1] = McpProtocolUtils::progressTokenToJson(progressNotificationParams.progressToken());

    if (progressNotificationParams.message().has_value()) {
        obj.insert("message"_L1, *progressNotificationParams.message());
    }
    if (progressNotificationParams.total().has_value()) {
        obj.insert("total"_L1, *progressNotificationParams.total());
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
