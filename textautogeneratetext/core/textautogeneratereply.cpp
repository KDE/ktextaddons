/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratereply.h"
#include "textautogeneratetextcore_debug.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;

static QString jsonValueToString(const QJsonValue &value)
{
    if (value.isString()) {
        return value.toString();
    }
    return value.toVariant().toString();
}

TextAutoGenerateReply::TextAutoGenerateReply(QNetworkReply *netReply, RequestTypes requestType, QObject *parent)
    : QObject{parent}
    , mReply{netReply}
    , mRequestType{requestType}
{
}

TextAutoGenerateReply::~TextAutoGenerateReply()
{
    // QNetworkAccessManager hands the reply over to its caller, so this wrapper owns it. The
    // manager parents replies to itself, which means forgetting to delete one keeps it -- and the
    // response it buffered -- alive for as long as the (singleton) access manager lives.
    if (mReply) {
        // Subclasses install lambdas that capture this and use mReply as their context object, so
        // detach them before abort() gets the chance to reenter them from a destructor.
        mReply->disconnect();
        mReply->abort();
        mReply->deleteLater();
    }
}

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

        TextAutoGenerateReply::ToolCallArgumentInfo toolInfo;
        toolInfo.toolName = toolName;
        toolInfo.id = obj["id"_L1].toString().toLatin1();
        toolInfo.arguments = argumentObj;
        toolInfo.index = index;
        toolInfo.toolCallArgument.reserve(argumentObj.size());
        for (auto it = argumentObj.constBegin(); it != argumentObj.constEnd(); ++it) {
            ToolCallArgument arg{.keyTool = it.key(), .value = jsonValueToString(it.value())};
            toolInfo.toolCallArgument.append(std::move(arg));
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
        QJsonObject argumentObj;
        if (const QJsonValue argumentsValue = functionObj["arguments"_L1]; argumentsValue.isObject()) {
            argumentObj = argumentsValue.toObject();
        } else if (argumentsValue.isString()) {
            const QString arguments = argumentsValue.toString();
            // qDebug() << " arguments: " << arguments;
            if (const QJsonDocument doc = QJsonDocument::fromJson(arguments.toUtf8()); doc.isObject()) {
                argumentObj = doc.object();
            }
        }
        TextAutoGenerateReply::ToolCallArgumentInfo toolInfo;
        toolInfo.toolName = toolName;
        toolInfo.id = obj["id"_L1].toString().toLatin1();
        toolInfo.arguments = argumentObj;
        toolInfo.index = index;
        toolInfo.toolCallArgument.reserve(argumentObj.size());
        for (auto it = argumentObj.constBegin(); it != argumentObj.constEnd(); ++it) {
            ToolCallArgument arg{.keyTool = it.key(), .value = jsonValueToString(it.value())};
            toolInfo.toolCallArgument.append(std::move(arg));
        }
        infos.append(toolInfo);
    }
    qCDebug(TEXTAUTOGENERATETEXT_CORE_LOG) << "TextAutoGenerateReply::parseToolCallsOpenAI infos: " << infos;
    return infos;
}

QList<TextAutoGenerateReply::ToolCallArgumentInfo> TextAutoGenerateReply::accumulateToolCallsOpenAI(const QJsonArray &array)
{
    for (const auto &value : array) {
        const QJsonObject obj = value.toObject();
        const QJsonObject functionObj = obj["function"_L1].toObject();
        const QByteArray id = obj["id"_L1].toString().toLatin1();
        const QByteArray name = functionObj["name"_L1].toString().toLatin1();
        int key = -1;
        if (obj.contains("index"_L1)) {
            key = obj.value("index"_L1).toInt();
        } else {
            // No index: find tool call from its id, otherwise it's a new tool call or next part of last one
            for (auto it = mStreamedToolCalls.cbegin(); it != mStreamedToolCalls.cend(); ++it) {
                if (!id.isEmpty() && it->id == id) {
                    key = it.key();
                    break;
                }
            }
            if (key == -1) {
                const int lastKey = mStreamedToolCalls.isEmpty() ? -1 : mStreamedToolCalls.lastKey();
                key = (lastKey == -1 || !id.isEmpty() || !name.isEmpty()) ? lastKey + 1 : lastKey;
            }
        }
        StreamedToolCall &call = mStreamedToolCalls[key];
        if (!id.isEmpty()) {
            call.id = id;
        }
        if (call.name.isEmpty()) {
            call.name = name;
        }
        if (const QJsonValue argumentsValue = functionObj["arguments"_L1]; argumentsValue.isObject()) {
            call.arguments = QString::fromUtf8(QJsonDocument(argumentsValue.toObject()).toJson(QJsonDocument::Compact));
        } else if (argumentsValue.isString()) {
            call.arguments += argumentsValue.toString();
        }
    }

    QList<TextAutoGenerateReply::ToolCallArgumentInfo> infos;
    infos.reserve(mStreamedToolCalls.count());
    for (auto it = mStreamedToolCalls.cbegin(); it != mStreamedToolCalls.cend(); ++it) {
        TextAutoGenerateReply::ToolCallArgumentInfo toolInfo;
        toolInfo.toolName = it->name;
        toolInfo.id = it->id;
        toolInfo.index = it.key();
        // Arguments are incomplete until the last part is received
        if (const QJsonDocument doc = QJsonDocument::fromJson(it->arguments.toUtf8()); doc.isObject()) {
            toolInfo.arguments = doc.object();
        }
        toolInfo.toolCallArgument.reserve(toolInfo.arguments.size());
        for (auto argIt = toolInfo.arguments.constBegin(); argIt != toolInfo.arguments.constEnd(); ++argIt) {
            toolInfo.toolCallArgument.append(ToolCallArgument{.keyTool = argIt.key(), .value = jsonValueToString(argIt.value())});
        }
        infos.append(std::move(toolInfo));
    }
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
    d.space() << "id:" << t.id;
    d.space() << "arguments:" << t.arguments;
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
    return other.toolCallArgument == toolCallArgument && other.toolName == toolName && other.id == id && other.arguments == arguments && other.index == index;
}

bool TextAutoGenerateReply::ToolCallArgument::operator==(const ToolCallArgument &other) const
{
    return other.keyTool == keyTool && other.value == value;
}
#include "moc_textautogeneratereply.cpp"
