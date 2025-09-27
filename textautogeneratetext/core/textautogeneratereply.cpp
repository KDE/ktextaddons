/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratereply.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkReply>

using namespace Qt::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateReply::TextAutoGenerateReply(QNetworkReply *netReply, RequestTypes requestType, QObject *parent)
    : QObject{parent}
    , mReply{netReply}
    , mRequestType{requestType}
{
}

TextAutoGenerateReply::~TextAutoGenerateReply() = default;

QList<TextAutoGenerateReply::ToolCallArgumentInfo> TextAutoGenerateReply::parseToolCalls(const QJsonArray &array) const
{
    qDebug() << " array " << array;
    QList<TextAutoGenerateReply::ToolCallArgumentInfo> infos;
    for (int i = 0; i < array.count(); ++i) {
        const QJsonObject obj = array[i].toObject();
        qDebug() << " obj " << obj;
        // QJsonArray([{"function":{"arguments":{"city":"Grenoble"},"name":"example_tool"}}])
        const QJsonObject functionObj = obj["function"_L1].toObject();
        const QString toolName = functionObj["name"_L1].toString();
        const QJsonObject argumentObj = functionObj["arguments"_L1].toObject();
        const QStringList functionKeys = argumentObj.keys();
        TextAutoGenerateReply::ToolCallArgumentInfo toolInfo;
        toolInfo.toolName = toolName;
        for (const QString &k : functionKeys) {
            if (k == u"arguments"_s) {
                continue;
            }
            const ToolCallArgument arg{.keyTool = k, .value = argumentObj[k].toString()};
            toolInfo.toolCallArgument.append(arg);
        }
        infos.append(toolInfo);
        qDebug() << " infos " << infos;
    }
    return infos;
}

const TextAutoGenerateReply::RequestTypes &TextAutoGenerateReply::requestType() const
{
    return mRequestType;
}

const TextAutoGenerateText::TextAutoGenerateTextReplyInfo &TextAutoGenerateReply::info() const
{
    return mInfo;
}

void TextAutoGenerateReply::cancel()
{
    if (mReply) {
        mReply->abort();
    }
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument &t)
{
    d.space() << "keyTool:" << t.keyTool;
    d.space() << "value:" << t.value;
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateReply::DownloadModelInfo &t)
{
    d.space() << "total:" << t.total;
    d.space() << "completed:" << t.completed;
    d.space() << "status:" << t.status;
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo &t)
{
    d.space() << "tool name:" << t.toolName;
    d.space() << "toolCallArgument:" << t.toolCallArgument;
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateReply::Response &t)
{
    d.space() << "Response:" << t.response;
    d.space() << "tool call response:" << t.info;
    return d;
}

bool TextAutoGenerateReply::Response::hasToolCallArguments() const
{
    return !info.isEmpty();
}

bool TextAutoGenerateReply::ToolCallArgumentInfo::operator==(const ToolCallArgumentInfo &other) const
{
    return other.toolCallArgument == toolCallArgument && other.toolName == toolName;
}

bool TextAutoGenerateReply::ToolCallArgument::operator==(const ToolCallArgument &other) const
{
    return other.keyTool == keyTool && other.value == value;
}
#include "moc_textautogeneratereply.cpp"
