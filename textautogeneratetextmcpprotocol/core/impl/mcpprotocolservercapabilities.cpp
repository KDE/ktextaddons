/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolservercapabilities.h"
#include <QDebug>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolServerCapabilities::McpProtocolServerCapabilities() = default;

McpProtocolServerCapabilities::~McpProtocolServerCapabilities() = default;

bool McpProtocolServerCapabilities::operator==(const McpProtocolServerCapabilities &other) const = default;

bool McpProtocolServerCapabilities::Prompts::operator==(const McpProtocolServerCapabilities::Prompts &other) const = default;
bool McpProtocolServerCapabilities::Resources::operator==(const McpProtocolServerCapabilities::Resources &other) const = default;
bool McpProtocolServerCapabilities::Tools::operator==(const McpProtocolServerCapabilities::Tools &other) const = default;
bool McpProtocolServerCapabilities::Tasks::operator==(const McpProtocolServerCapabilities::Tasks &other) const = default;
bool McpProtocolServerCapabilities::Tasks::Requests::operator==(const McpProtocolServerCapabilities::Tasks::Requests &other) const = default;
bool McpProtocolServerCapabilities::Tasks::Requests::Tools::operator==(const McpProtocolServerCapabilities::Tasks::Requests::Tools &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolServerCapabilities &t)
{
    d.space() << "completions:" << t.completions();
    d.space() << "experimental:" << t.experimental();
    d.space() << "logging:" << t.logging();
    d.space() << "prompts:" << t.prompts();
    d.space() << "resources:" << t.resources();
    d.space() << "tasks:" << t.tasks();
    d.space() << "tools:" << t.tools();
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolServerCapabilities::Prompts &t)
{
    d.space() << "listChanged:" << t.listChanged();
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolServerCapabilities::Tools &t)
{
    d.space() << "listChanged:" << t.listChanged();
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolServerCapabilities::Tasks &t)
{
    d.space() << "cancel:" << t.cancel();
    d.space() << "list:" << t.list();
    d.space() << "requests:" << t.requests();
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolServerCapabilities::Tasks::Requests &t)
{
    d.space() << "tools:" << t.tools();
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolServerCapabilities::Tasks::Requests::Tools &t)
{
    d.space() << "call:" << t.call();
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolServerCapabilities::Resources &t)
{
    d.space() << "listChanged:" << t.listChanged();
    d.space() << "subscribe:" << t.subscribe();
    return d;
}

McpProtocolServerCapabilities McpProtocolServerCapabilities::fromJson(const QJsonObject &obj)
{
    McpProtocolServerCapabilities capabilities;
    if (obj.contains("completions"_L1) && obj["completions"_L1].isObject()) {
        const QJsonObject mapObj_completions = obj["completions"_L1].toObject();
        QMap<QString, QJsonValue> map_completions;
        for (auto it = mapObj_completions.constBegin(); it != mapObj_completions.constEnd(); ++it) {
            map_completions.insert(it.key(), it.value());
        }
        capabilities.setCompletions(map_completions);
    }
    if (obj.contains("experimental"_L1) && obj["experimental"_L1].isObject()) {
        const QJsonObject mapObj_experimental = obj["experimental"_L1].toObject();
        QMap<QString, QJsonObject> map_experimental;
        for (auto it = mapObj_experimental.constBegin(); it != mapObj_experimental.constEnd(); ++it) {
            map_experimental.insert(it.key(), it.value().toObject());
        }
        capabilities.setExperimental(map_experimental);
    }
    if (obj.contains("logging"_L1) && obj["logging"_L1].isObject()) {
        const QJsonObject mapObj_logging = obj["logging"_L1].toObject();
        QMap<QString, QJsonValue> map_logging;
        for (auto it = mapObj_logging.constBegin(); it != mapObj_logging.constEnd(); ++it) {
            map_logging.insert(it.key(), it.value());
        }
        capabilities.setLogging(map_logging);
    }
    if (obj.contains("prompts"_L1) && obj["prompts"_L1].isObject()) {
        capabilities.setPrompts(McpProtocolServerCapabilities::Prompts::fromJson(obj["prompts"_L1].toObject()));
    }
    if (obj.contains("resources"_L1) && obj["resources"_L1].isObject()) {
        capabilities.setResources(McpProtocolServerCapabilities::Resources::fromJson(obj["resources"_L1].toObject()));
    }
    if (obj.contains("tasks"_L1) && obj["tasks"_L1].isObject()) {
        capabilities.setTasks(McpProtocolServerCapabilities::Tasks::fromJson(obj["tasks"_L1].toObject()));
    }
    if (obj.contains("tools"_L1) && obj["tools"_L1].isObject()) {
        capabilities.setTools(McpProtocolServerCapabilities::Tools::fromJson(obj["tools"_L1].toObject()));
    }
    return capabilities;
}

QJsonObject McpProtocolServerCapabilities::toJson(const McpProtocolServerCapabilities &capabilities)
{
    QJsonObject obj;
    if (capabilities.completions().has_value()) {
        QJsonObject map_completions;
        const auto completions = *capabilities.completions();
        for (auto it = completions.constBegin(); it != completions.constEnd(); ++it) {
            map_completions.insert(it.key(), it.value());
        }
        obj.insert("completions"_L1, map_completions);
    }
    if (capabilities.experimental().has_value()) {
        QJsonObject map_experimental;
        const auto experimental = *capabilities.experimental();
        for (auto it = experimental.constBegin(); it != experimental.constEnd(); ++it) {
            map_experimental.insert(it.key(), QJsonValue(it.value()));
        }
        obj.insert("experimental"_L1, map_experimental);
    }
    if (capabilities.logging().has_value()) {
        QJsonObject map_logging;
        const auto logging = *capabilities.logging();
        for (auto it = logging.constBegin(); it != logging.constEnd(); ++it) {
            map_logging.insert(it.key(), it.value());
        }
        obj.insert("logging"_L1, map_logging);
    }
    if (capabilities.prompts().has_value()) {
        obj.insert("prompts"_L1, McpProtocolServerCapabilities::Prompts::toJson(*capabilities.prompts()));
    }
    if (capabilities.resources().has_value()) {
        obj.insert("resources"_L1, McpProtocolServerCapabilities::Resources::toJson(*capabilities.resources()));
    }
    if (capabilities.tasks().has_value()) {
        obj.insert("tasks"_L1, McpProtocolServerCapabilities::Tasks::toJson(*capabilities.tasks()));
    }
    if (capabilities.tools().has_value()) {
        obj.insert("tools"_L1, McpProtocolServerCapabilities::Tools::toJson(*capabilities.tools()));
    }
    return obj;
}

McpProtocolServerCapabilities::Prompts McpProtocolServerCapabilities::Prompts::fromJson(const QJsonObject &obj)
{
    McpProtocolServerCapabilities::Prompts prompts;
    if (obj.contains("listChanged"_L1)) {
        prompts.listChanged(obj.value("listChanged"_L1).toBool());
    }
    return prompts;
}

QJsonObject McpProtocolServerCapabilities::Prompts::toJson(const McpProtocolServerCapabilities::Prompts &prompts)
{
    QJsonObject obj;
    if (prompts.listChanged().has_value()) {
        obj["listChanged"_L1] = *prompts.listChanged();
    }
    return obj;
}

McpProtocolServerCapabilities::Resources McpProtocolServerCapabilities::Resources::fromJson(const QJsonObject &obj)
{
    McpProtocolServerCapabilities::Resources resources;
    if (obj.contains("listChanged"_L1)) {
        resources.listChanged(obj.value("listChanged"_L1).toBool());
    }
    if (obj.contains("subscribe"_L1)) {
        resources.subscribe(obj.value("subscribe"_L1).toBool());
    }
    return resources;
}

QJsonObject McpProtocolServerCapabilities::Resources::toJson(const McpProtocolServerCapabilities::Resources &resources)
{
    QJsonObject obj;
    if (resources.listChanged().has_value()) {
        obj["listChanged"_L1] = *resources.listChanged();
    }
    if (resources.subscribe().has_value()) {
        obj["subscribe"_L1] = *resources.subscribe();
    }
    return obj;
}

McpProtocolServerCapabilities::Tools McpProtocolServerCapabilities::Tools::fromJson(const QJsonObject &obj)
{
    McpProtocolServerCapabilities::Tools tools;
    if (obj.contains("listChanged"_L1)) {
        tools.listChanged(obj.value("listChanged"_L1).toBool());
    }
    return tools;
}

QJsonObject McpProtocolServerCapabilities::Tools::toJson(const McpProtocolServerCapabilities::Tools &tools)
{
    QJsonObject obj;
    if (tools.listChanged().has_value()) {
        obj["listChanged"_L1] = *tools.listChanged();
    }
    return obj;
}

McpProtocolServerCapabilities::Tasks McpProtocolServerCapabilities::Tasks::fromJson(const QJsonObject &obj)
{
    McpProtocolServerCapabilities::Tasks tasks;
    if (obj.contains("cancel"_L1) && obj["cancel"_L1].isObject()) {
        const QJsonObject mapObj_cancel = obj["cancel"_L1].toObject();
        QMap<QString, QJsonValue> map_cancel;
        for (auto it = mapObj_cancel.constBegin(); it != mapObj_cancel.constEnd(); ++it) {
            map_cancel.insert(it.key(), it.value());
        }
        tasks.setCancel(map_cancel);
    }
    if (obj.contains("list"_L1) && obj["list"_L1].isObject()) {
        const QJsonObject mapObj_list = obj["list"_L1].toObject();
        QMap<QString, QJsonValue> map_list;
        for (auto it = mapObj_list.constBegin(); it != mapObj_list.constEnd(); ++it) {
            map_list.insert(it.key(), it.value());
        }
        tasks.setList(map_list);
    }
    if (obj.contains("requests"_L1) && obj["requests"_L1].isObject()) {
        tasks.setRequests(McpProtocolServerCapabilities::Tasks::Requests::fromJson(obj["requests"_L1].toObject()));
    }
    return tasks;
}

QJsonObject McpProtocolServerCapabilities::Tasks::toJson(const McpProtocolServerCapabilities::Tasks &tasks)
{
    QJsonObject obj;
    if (tasks.cancel().has_value()) {
        QJsonObject map_cancel;
        const auto cancel = *tasks.cancel();
        for (auto it = cancel.constBegin(); it != cancel.constEnd(); ++it) {
            map_cancel.insert(it.key(), it.value());
        }
        obj.insert("cancel"_L1, map_cancel);
    }
    if (tasks.list().has_value()) {
        QJsonObject map_list;
        const auto list = *tasks.list();
        for (auto it = list.constBegin(); it != list.constEnd(); ++it) {
            map_list.insert(it.key(), it.value());
        }
        obj.insert("list"_L1, map_list);
    }
    if (tasks.requests().has_value()) {
        obj.insert("requests"_L1, McpProtocolServerCapabilities::Tasks::Requests::toJson(*tasks.requests()));
    }
    return obj;
}

McpProtocolServerCapabilities::Tasks::Requests McpProtocolServerCapabilities::Tasks::Requests::fromJson(const QJsonObject &obj)
{
    McpProtocolServerCapabilities::Tasks::Requests requests;
    if (obj.contains("tools"_L1) && obj["tools"_L1].isObject()) {
        requests.setTools(McpProtocolServerCapabilities::Tasks::Requests::Tools::fromJson(obj["tools"_L1].toObject()));
    }
    return requests;
}

QJsonObject McpProtocolServerCapabilities::Tasks::Requests::toJson(const McpProtocolServerCapabilities::Tasks::Requests &requests)
{
    QJsonObject obj;
    if (requests.tools().has_value()) {
        obj.insert("tools"_L1, McpProtocolServerCapabilities::Tasks::Requests::Tools::toJson(*requests.tools()));
    }
    return obj;
}

McpProtocolServerCapabilities::Tasks::Requests::Tools McpProtocolServerCapabilities::Tasks::Requests::Tools::fromJson(const QJsonObject &obj)
{
    McpProtocolServerCapabilities::Tasks::Requests::Tools tools;
    if (obj.contains("call"_L1) && obj["call"_L1].isObject()) {
        const QJsonObject mapObj_call = obj["call"_L1].toObject();
        QMap<QString, QJsonValue> map_call;
        for (auto it = mapObj_call.constBegin(); it != mapObj_call.constEnd(); ++it) {
            map_call.insert(it.key(), it.value());
        }
        tools.setCall(map_call);
    }
    return tools;
}

QJsonObject McpProtocolServerCapabilities::Tasks::Requests::Tools::toJson(const McpProtocolServerCapabilities::Tasks::Requests::Tools &tools)
{
    QJsonObject obj;
    if (tools.call().has_value()) {
        QJsonObject map_call;
        const auto call = *tools.call();
        for (auto it = call.constBegin(); it != call.constEnd(); ++it) {
            map_call.insert(it.key(), it.value());
        }
        obj.insert("call"_L1, map_call);
    }
    return obj;
}

McpProtocolServerCapabilities::Prompts &McpProtocolServerCapabilities::Prompts::listChanged(std::optional<bool> v)
{
    mListChanged = v;
    return *this;
}

const std::optional<bool> &McpProtocolServerCapabilities::Prompts::listChanged() const
{
    return mListChanged;
}

McpProtocolServerCapabilities::Resources &McpProtocolServerCapabilities::Resources::listChanged(std::optional<bool> v)
{
    mListChanged = v;
    return *this;
}

McpProtocolServerCapabilities::Resources &McpProtocolServerCapabilities::Resources::subscribe(std::optional<bool> v)
{
    mSubscribe = v;
    return *this;
}

const std::optional<bool> &McpProtocolServerCapabilities::Resources::listChanged() const
{
    return mListChanged;
}

const std::optional<bool> &McpProtocolServerCapabilities::Resources::subscribe() const
{
    return mSubscribe;
}

McpProtocolServerCapabilities::Tools &McpProtocolServerCapabilities::Tools::listChanged(std::optional<bool> v)
{
    mListChanged = v;
    return *this;
}

const std::optional<bool> &McpProtocolServerCapabilities::Tools::listChanged() const
{
    return mListChanged;
}

std::optional<QMap<QString, QJsonValue>> McpProtocolServerCapabilities::Tasks::cancel() const
{
    return mCancel;
}

void McpProtocolServerCapabilities::Tasks::setCancel(std::optional<QMap<QString, QJsonValue>> newCancel)
{
    mCancel = std::move(newCancel);
}

std::optional<QMap<QString, QJsonValue>> McpProtocolServerCapabilities::Tasks::list() const
{
    return mList;
}

void McpProtocolServerCapabilities::Tasks::setList(std::optional<QMap<QString, QJsonValue>> newList)
{
    mList = std::move(newList);
}

std::optional<McpProtocolServerCapabilities::Tasks::Requests> McpProtocolServerCapabilities::Tasks::requests() const
{
    return mRequests;
}

void McpProtocolServerCapabilities::Tasks::setRequests(std::optional<Requests> newRequests)
{
    mRequests = std::move(newRequests);
}

std::optional<McpProtocolServerCapabilities::Tasks::Requests::Tools> McpProtocolServerCapabilities::Tasks::Requests::tools() const
{
    return mTools;
}

void McpProtocolServerCapabilities::Tasks::Requests::setTools(std::optional<Tools> newTools)
{
    mTools = std::move(newTools);
}

std::optional<QMap<QString, QJsonValue>> McpProtocolServerCapabilities::Tasks::Requests::Tools::call() const
{
    return mCall;
}

void McpProtocolServerCapabilities::Tasks::Requests::Tools::setCall(std::optional<QMap<QString, QJsonValue>> newCall)
{
    mCall = std::move(newCall);
}

std::optional<QMap<QString, QJsonValue>> McpProtocolServerCapabilities::completions() const
{
    return mCompletions;
}

void McpProtocolServerCapabilities::setCompletions(std::optional<QMap<QString, QJsonValue>> newCompletions)
{
    mCompletions = std::move(newCompletions);
}

std::optional<QMap<QString, QJsonObject>> McpProtocolServerCapabilities::experimental() const
{
    return mExperimental;
}

void McpProtocolServerCapabilities::setExperimental(std::optional<QMap<QString, QJsonObject>> newExperimental)
{
    mExperimental = std::move(newExperimental);
}

std::optional<QMap<QString, QJsonValue>> McpProtocolServerCapabilities::logging() const
{
    return mLogging;
}

void McpProtocolServerCapabilities::setLogging(std::optional<QMap<QString, QJsonValue>> newLogging)
{
    mLogging = std::move(newLogging);
}

std::optional<McpProtocolServerCapabilities::Prompts> McpProtocolServerCapabilities::prompts() const
{
    return mPrompts;
}

void McpProtocolServerCapabilities::setPrompts(std::optional<Prompts> newPrompts)
{
    mPrompts = std::move(newPrompts);
}

std::optional<McpProtocolServerCapabilities::Resources> McpProtocolServerCapabilities::resources() const
{
    return mResources;
}

void McpProtocolServerCapabilities::setResources(std::optional<Resources> newResources)
{
    mResources = std::move(newResources);
}

std::optional<McpProtocolServerCapabilities::Tasks> McpProtocolServerCapabilities::tasks() const
{
    return mTasks;
}

void McpProtocolServerCapabilities::setTasks(std::optional<Tasks> newTasks)
{
    mTasks = std::move(newTasks);
}

std::optional<McpProtocolServerCapabilities::Tools> McpProtocolServerCapabilities::tools() const
{
    return mTools;
}

void McpProtocolServerCapabilities::setTools(std::optional<Tools> newTools)
{
    mTools = std::move(newTools);
}
