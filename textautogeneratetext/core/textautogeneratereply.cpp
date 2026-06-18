/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratereply.h"
#include "textautogeneratetextcore_debug.h"
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateReply::TextAutoGenerateReply(QNetworkReply *netReply, RequestTypes requestType, QObject *parent)
    : QObject{parent}
    , mReply{netReply}
    , mRequestType{requestType}
{
}

TextAutoGenerateReply::~TextAutoGenerateReply() = default;

QList<TextAutoGenerateReply::ToolCallArgumentInfo> TextAutoGenerateReply::parseToolCallsOllama(const QJsonArray &array) const
{
    // qDebug() << " array " << array;
    QList<TextAutoGenerateReply::ToolCallArgumentInfo> infos;
    for (int i = 0; i < array.count(); ++i) {
        const QJsonObject obj = array[i].toObject();
        // qDebug() << " obj " << obj;
        // QJsonArray([{"function":{"arguments":{"city":"Grenoble"},"name":"example_tool"}}])
        const QJsonObject functionObj = obj["function"_L1].toObject();
        qCDebug(TEXTAUTOGENERATETEXT_CORE_LOG) << " functionObj " << functionObj;
        const QByteArray toolName = functionObj["name"_L1].toString().toLatin1();
        const QJsonObject argumentObj = functionObj["arguments"_L1].toObject();
        int index = -1;
        if (obj.contains("index"_L1)) {
            index = obj.value("index"_L1).toInteger();
        } else if (functionObj.contains("index"_L1)) {
            index = functionObj.value("index"_L1).toInteger();
        }
        if (index != -1) {
            qCDebug(TEXTAUTOGENERATETEXT_CORE_LOG) << " INDEX : " << index;
        }

        const QStringList functionKeys = argumentObj.keys();
        TextAutoGenerateReply::ToolCallArgumentInfo toolInfo;
        toolInfo.toolName = toolName;
        toolInfo.index = index;
        for (const QString &k : functionKeys) {
            const ToolCallArgument arg{.keyTool = k, .value = argumentObj[k].toString()};
            toolInfo.toolCallArgument.append(arg);
        }
        infos.append(toolInfo);
    }
    qCDebug(TEXTAUTOGENERATETEXT_CORE_LOG) << "TextAutoGenerateReply::parseToolCallsOllam infos " << infos;
    return infos;
}

QList<TextAutoGenerateReply::ToolCallArgumentInfo> TextAutoGenerateReply::parseToolCallsOpenAI(const QJsonArray &array) const
{
    qCDebug(TEXTAUTOGENERATETEXT_CORE_LOG) << " TextAutoGenerateReply::parseToolCallsOpenAI: " << array;
    QList<TextAutoGenerateReply::ToolCallArgumentInfo> infos;
    for (int i = 0; i < array.count(); ++i) {
        const QJsonObject obj = array[i].toObject();
        // qDebug() << " obj " << obj;
        // {\"id\":\"QNfTI1iiJ\",\"function\":{\"name\":\"current_date_time_tool\",\"arguments\":\"{\\\"currentdatetime\\\" :\\\"time\\\"}\"},\"index\":0}]}
        const QJsonObject functionObj = obj["function"_L1].toObject();
        qCDebug(TEXTAUTOGENERATETEXT_CORE_LOG) << " functionObj " << functionObj;
        const QByteArray toolName = functionObj["name"_L1].toString().toLatin1();

        int index = -1;
        if (obj.contains("index"_L1)) {
            index = obj.value("index"_L1).toInteger();
        } else if (functionObj.contains("index"_L1)) {
            index = functionObj.value("index"_L1).toInteger();
        }
        if (index != -1) {
            qCDebug(TEXTAUTOGENERATETEXT_CORE_LOG) << " INDEX : " << index;
        }
        const QString arguments = functionObj["arguments"_L1].toString();
        // qDebug() << " arguments: " << arguments;
        const QJsonDocument doc = QJsonDocument::fromJson(arguments.toLatin1());

        const QJsonObject argumentObj = doc.object();
        const QStringList functionKeys = argumentObj.keys();
        TextAutoGenerateReply::ToolCallArgumentInfo toolInfo;
        toolInfo.toolName = toolName;
        toolInfo.index = index;
        for (const QString &k : functionKeys) {
            const ToolCallArgument arg{.keyTool = k, .value = argumentObj[k].toString()};
            toolInfo.toolCallArgument.append(arg);
        }
        infos.append(toolInfo);
    }
    qCDebug(TEXTAUTOGENERATETEXT_CORE_LOG) << "TextAutoGenerateReply::parseToolCallsOpenAI infos: " << infos;
    return infos;
}

const TextAutoGenerateReply::RequestTypes &TextAutoGenerateReply::requestType() const
{
    return mRequestType;
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
    d.space() << "error:" << t.error;
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo &t)
{
    d.space() << "tool name:" << t.toolName;
    d.space() << "toolCallArgument:" << t.toolCallArgument;
    d.space() << "index:" << t.index;
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateReply::Response &t)
{
    d.space() << "Response:" << t.response;
    d.space() << "thinking:" << t.thinking;
    d.space() << "tool call response:" << t.info;
    d.space() << "Reply info:" << t.replyInfo;
    return d;
}

bool TextAutoGenerateReply::Response::hasToolCallArguments() const
{
    return !info.isEmpty();
}

bool TextAutoGenerateReply::ToolCallArgumentInfo::operator==(const ToolCallArgumentInfo &other) const
{
    return other.toolCallArgument == toolCallArgument && other.toolName == toolName && other.index == index;
}

bool TextAutoGenerateReply::ToolCallArgument::operator==(const ToolCallArgument &other) const
{
    return other.keyTool == keyTool && other.value == value;
}
#include "moc_textautogeneratereply.cpp"
