/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolcreatemessagerequestparams.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolCreateMessageRequestParams::McpProtocolCreateMessageRequestParams() = default;

bool McpProtocolCreateMessageRequestParams::operator==(const McpProtocolCreateMessageRequestParams &other) const = default;
bool McpProtocolCreateMessageRequestParams::Meta::operator==(const McpProtocolCreateMessageRequestParams::Meta &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageRequestParams &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "maxTokens:" << t.maxTokens();
    d.space() << "messages:" << t.messages();
    if (t.includeContext().has_value()) {
        d.space() << "includeContext:" << McpProtocolCreateMessageRequestParams::convertIncludeContextToString(*t.includeContext());
    }
    d.space() << "metadata:" << t.metadata();
    d.space() << "modelPreferences:" << t.modelPreferences();
    d.space() << "stopSequences:" << t.stopSequences();
    d.space() << "systemPrompt:" << t.systemPrompt();
    d.space() << "task:" << t.task();
    d.space() << "temperature:" << t.temperature();
    d.space() << "toolChoice:" << t.toolChoice();
    d.space() << "tools:" << t.tools();
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageRequestParams::Meta &t)
{
    d.space() << "progressToken:" << t.progressToken();
    return d;
}

McpProtocolCreateMessageRequestParams::Meta McpProtocolCreateMessageRequestParams::Meta::fromJson(const QJsonObject &obj)
{
    McpProtocolCreateMessageRequestParams::Meta meta;
    if (obj.contains("progressToken"_L1)) {
        meta.setProgressToken(McpProtocolUtils::progressTokenFromJson(obj["progressToken"_L1]));
    }
    return meta;
}

QJsonObject McpProtocolCreateMessageRequestParams::Meta::toJson(const McpProtocolCreateMessageRequestParams::Meta &image)
{
    QJsonObject obj;
    if (image.progressToken().has_value()) {
        obj["progressToken"_L1] = McpProtocolUtils::progressTokenToJson(*image.progressToken());
    }
    return obj;
}

McpProtocolCreateMessageRequestParams McpProtocolCreateMessageRequestParams::fromJson(const QJsonObject &obj)
{
    McpProtocolCreateMessageRequestParams prompt;
    if (!obj.contains("maxTokens"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: maxTokens";
        return prompt;
    }
    if (!obj.contains("messages"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: messages";
        return prompt;
    }
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        prompt.setMeta(McpProtocolCreateMessageRequestParams::Meta::fromJson(metaValue.toObject()));
    }
    if (obj.contains("includeContext"_L1)) {
        prompt.setIncludeContext(convertIncludeContextFromString(obj.value("includeContext"_L1).toString()));
    }
    prompt.setMaxTokens(obj.value("maxTokens"_L1).toInt());
    if (obj["messages"_L1].isArray()) {
        const QJsonArray arr = obj["messages"_L1].toArray();
        QList<McpProtocolSamplingMessage> messages;
        messages.reserve(arr.count());
        for (const QJsonValue &v : arr) {
            messages.append(McpProtocolSamplingMessage::fromJson(v.toObject()));
        }
        prompt.setMessages(messages);
    }
    if (const QJsonValue metadataValue = obj.value("metadata"_L1); metadataValue.isObject()) {
        const QJsonObject mapObj_metadata = metadataValue.toObject();
        QMap<QString, QJsonValue> map_metadata;
        for (auto it = mapObj_metadata.constBegin(); it != mapObj_metadata.constEnd(); ++it) {
            map_metadata.insert(it.key(), it.value());
        }
        prompt.setMetadata(map_metadata);
    }
    if (const QJsonValue modelPreferencesValue = obj.value("modelPreferences"_L1); modelPreferencesValue.isObject()) {
        prompt.setModelPreferences(McpProtocolModelPreferences::fromJson(modelPreferencesValue.toObject()));
    }
    if (const QJsonValue stopSequencesValue = obj.value("stopSequences"_L1); stopSequencesValue.isArray()) {
        const QJsonArray arr = stopSequencesValue.toArray();
        QStringList list_stopSequences;
        list_stopSequences.reserve(arr.count());
        for (const QJsonValue &v : arr) {
            list_stopSequences.append(v.toString());
        }
        prompt.setStopSequences(list_stopSequences);
    }
    if (obj.contains("systemPrompt"_L1)) {
        prompt.setSystemPrompt(obj.value("systemPrompt"_L1).toString());
    }
    if (const QJsonValue taskValue = obj.value("task"_L1); taskValue.isObject()) {
        prompt.setTask(McpProtocolTaskMetadata::fromJson(taskValue.toObject()));
    }
    if (obj.contains("temperature"_L1)) {
        prompt.setTemperature(obj.value("temperature"_L1).toDouble());
    }
    if (const QJsonValue toolChoiceValue = obj.value("toolChoice"_L1); toolChoiceValue.isObject()) {
        prompt.setToolChoice(McpProtocolToolChoice::fromJson(toolChoiceValue.toObject()));
    }
    if (const QJsonValue toolsValue = obj.value("tools"_L1); toolsValue.isArray()) {
        const QJsonArray arr = toolsValue.toArray();
        QList<McpProtocolTool> tools;
        tools.reserve(arr.count());
        for (const QJsonValue &v : arr) {
            tools.append(McpProtocolTool::fromJson(v.toObject()));
        }
        prompt.setTools(tools);
    }
    return prompt;
}

QJsonObject McpProtocolCreateMessageRequestParams::toJson(const McpProtocolCreateMessageRequestParams &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolCreateMessageRequestParams::Meta::toJson(*boolean.meta());
    }
    obj["maxTokens"_L1] = boolean.maxTokens();
    QJsonArray arr_messages;
    for (const auto &v : boolean.messages()) {
        arr_messages.append(McpProtocolSamplingMessage::toJson(v));
    }
    obj["messages"_L1] = arr_messages;
    if (boolean.includeContext().has_value()) {
        obj.insert("includeContext"_L1, convertIncludeContextToString(*boolean.includeContext()));
    }
    if (boolean.metadata().has_value()) {
        QJsonObject map_metadata;
        const auto metadata = *boolean.metadata();
        for (auto it = metadata.constBegin(); it != metadata.constEnd(); ++it) {
            map_metadata.insert(it.key(), it.value());
        }
        obj.insert("metadata"_L1, map_metadata);
    }
    if (boolean.modelPreferences().has_value()) {
        obj.insert("modelPreferences"_L1, McpProtocolModelPreferences::toJson(*boolean.modelPreferences()));
    }
    if (boolean.stopSequences().has_value()) {
        QJsonArray arr_stopSequences;
        const auto stopSequences = *boolean.stopSequences();
        for (const auto &v : stopSequences) {
            arr_stopSequences.append(v);
        }
        obj.insert("stopSequences"_L1, arr_stopSequences);
    }
    if (boolean.systemPrompt().has_value()) {
        obj.insert("systemPrompt"_L1, *boolean.systemPrompt());
    }
    if (boolean.task().has_value()) {
        obj.insert("task"_L1, McpProtocolTaskMetadata::toJson(*boolean.task()));
    }
    if (boolean.temperature().has_value()) {
        obj.insert("temperature"_L1, *boolean.temperature());
    }
    if (boolean.toolChoice().has_value()) {
        obj.insert("toolChoice"_L1, McpProtocolToolChoice::toJson(*boolean.toolChoice()));
    }
    if (boolean.tools().has_value()) {
        QJsonArray arr_tools;
        const auto tools = *boolean.tools();
        for (const auto &v : tools) {
            arr_tools.append(McpProtocolTool::toJson(v));
        }
        obj.insert("tools"_L1, arr_tools);
    }
    return obj;
}

std::optional<McpProtocolCreateMessageRequestParams::Meta> McpProtocolCreateMessageRequestParams::meta() const
{
    return mMeta;
}

void McpProtocolCreateMessageRequestParams::setMeta(std::optional<Meta> newMeta)
{
    mMeta = std::move(newMeta);
}

std::optional<McpProtocolCreateMessageRequestParams::IncludeContext> McpProtocolCreateMessageRequestParams::includeContext() const
{
    return mIncludeContext;
}

void McpProtocolCreateMessageRequestParams::setIncludeContext(std::optional<IncludeContext> newIncludeContext)
{
    mIncludeContext = newIncludeContext;
}

int McpProtocolCreateMessageRequestParams::maxTokens() const
{
    return mMaxTokens;
}

void McpProtocolCreateMessageRequestParams::setMaxTokens(int newMaxTokens)
{
    mMaxTokens = newMaxTokens;
}

std::optional<QMap<QString, QJsonValue>> McpProtocolCreateMessageRequestParams::metadata() const
{
    return mMetadata;
}

void McpProtocolCreateMessageRequestParams::setMetadata(std::optional<QMap<QString, QJsonValue>> newMetadata)
{
    mMetadata = std::move(newMetadata);
}

std::optional<McpProtocolModelPreferences> McpProtocolCreateMessageRequestParams::modelPreferences() const
{
    return mModelPreferences;
}

void McpProtocolCreateMessageRequestParams::setModelPreferences(std::optional<McpProtocolModelPreferences> newModelPreferences)
{
    mModelPreferences = std::move(newModelPreferences);
}

QList<McpProtocolSamplingMessage> McpProtocolCreateMessageRequestParams::messages() const
{
    return mMessages;
}

void McpProtocolCreateMessageRequestParams::setMessages(const QList<McpProtocolSamplingMessage> &newMessages)
{
    mMessages = newMessages;
}

std::optional<QStringList> McpProtocolCreateMessageRequestParams::stopSequences() const
{
    return mStopSequences;
}

void McpProtocolCreateMessageRequestParams::setStopSequences(std::optional<QStringList> newStopSequences)
{
    mStopSequences = std::move(newStopSequences);
}

std::optional<QString> McpProtocolCreateMessageRequestParams::systemPrompt() const
{
    return mSystemPrompt;
}

void McpProtocolCreateMessageRequestParams::setSystemPrompt(std::optional<QString> newSystemPrompt)
{
    mSystemPrompt = std::move(newSystemPrompt);
}

std::optional<McpProtocolTaskMetadata> McpProtocolCreateMessageRequestParams::task() const
{
    return mTask;
}

void McpProtocolCreateMessageRequestParams::setTask(std::optional<McpProtocolTaskMetadata> newTask)
{
    mTask = std::move(newTask);
}

std::optional<double> McpProtocolCreateMessageRequestParams::temperature() const
{
    return mTemperature;
}

void McpProtocolCreateMessageRequestParams::setTemperature(std::optional<double> newTemperature)
{
    mTemperature = newTemperature;
}

std::optional<McpProtocolToolChoice> McpProtocolCreateMessageRequestParams::toolChoice() const
{
    return mToolChoice;
}

void McpProtocolCreateMessageRequestParams::setToolChoice(std::optional<McpProtocolToolChoice> newToolChoice)
{
    mToolChoice = newToolChoice;
}

std::optional<QList<McpProtocolTool>> McpProtocolCreateMessageRequestParams::tools() const
{
    return mTools;
}

void McpProtocolCreateMessageRequestParams::setTools(std::optional<QList<McpProtocolTool>> newTools)
{
    mTools = std::move(newTools);
}

std::optional<McpProtocolUtils::ProgressToken> McpProtocolCreateMessageRequestParams::Meta::progressToken() const
{
    return mProgressToken;
}

void McpProtocolCreateMessageRequestParams::Meta::setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken)
{
    mProgressToken = std::move(newProgressToken);
}

QString McpProtocolCreateMessageRequestParams::convertIncludeContextToString(McpProtocolCreateMessageRequestParams::IncludeContext includeContext)
{
    switch (includeContext) {
    case IncludeContext::allServers:
        return u"allServers"_s;
    case IncludeContext::none:
        return u"none"_s;
    case IncludeContext::thisServer:
        return u"thisServer"_s;
    case IncludeContext::Unknown:
        return {};
    }
    return {};
}

McpProtocolCreateMessageRequestParams::IncludeContext McpProtocolCreateMessageRequestParams::convertIncludeContextFromString(const QString &str)
{
    if (str == "allServers"_L1) {
        return McpProtocolCreateMessageRequestParams::IncludeContext::allServers;
    }
    if (str == "none"_L1) {
        return McpProtocolCreateMessageRequestParams::IncludeContext::none;
    }
    if (str == "thisServer"_L1) {
        return McpProtocolCreateMessageRequestParams::IncludeContext::thisServer;
    }
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid CreateMessageRequestParams::IncludeContext value: " << str;
    return McpProtocolCreateMessageRequestParams::IncludeContext::Unknown;
}
