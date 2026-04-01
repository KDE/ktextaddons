/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolclientcapabilities.h"
#include <QDebug>

using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolClientCapabilities::McpProtocolClientCapabilities() = default;

McpProtocolClientCapabilities::~McpProtocolClientCapabilities() = default;

bool McpProtocolClientCapabilities::operator==(const McpProtocolClientCapabilities &other) const = default;

bool McpProtocolClientCapabilities::Elicitation::operator==(const McpProtocolClientCapabilities::Elicitation &other) const = default;
bool McpProtocolClientCapabilities::Roots::operator==(const McpProtocolClientCapabilities::Roots &other) const = default;
bool McpProtocolClientCapabilities::Sampling::operator==(const McpProtocolClientCapabilities::Sampling &other) const = default;
bool McpProtocolClientCapabilities::Tasks::operator==(const McpProtocolClientCapabilities::Tasks &other) const = default;
bool McpProtocolClientCapabilities::Tasks::Requests::operator==(const McpProtocolClientCapabilities::Tasks::Requests &other) const = default;

std::optional<McpProtocolClientCapabilities::Tasks::Requests::Elicitation> McpProtocolClientCapabilities::Tasks::Requests::elicitation() const
{
    return mElicitation;
}

void McpProtocolClientCapabilities::Tasks::Requests::setElicitation(std::optional<Elicitation> newElicitation)
{
    mElicitation = newElicitation;
}

std::optional<McpProtocolClientCapabilities::Tasks::Requests::Sampling> McpProtocolClientCapabilities::Tasks::Requests::sampling() const
{
    return mSampling;
}

void McpProtocolClientCapabilities::Tasks::Requests::setSampling(std::optional<Sampling> newSampling)
{
    mSampling = newSampling;
}

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolClientCapabilities::Roots &t)
{
    d.space() << "listChanged:" << t.listChanged();
    return d;
}

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolClientCapabilities &t)
{
    d.space() << "elicitation:" << t.elicitation();
    d.space() << "roots:" << t.roots();
    d.space() << "sampling:" << t.sampling();
    d.space() << "experimental:" << t.experimental();
    d.space() << "tasks:" << t.tasks();
    return d;
}

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolClientCapabilities::Elicitation &t)
{
    d.space() << "form:" << t.form();
    d.space() << "url:" << t.url();
    return d;
}

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolClientCapabilities::Sampling &t)
{
    d.space() << "tools:" << t.tools();
    d.space() << "context:" << t.context();
    return d;
}

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolClientCapabilities::Tasks &t)
{
    d.space() << "cancel:" << t.cancel();
    d.space() << "list:" << t.list();
    d.space() << "requests:" << t.requests();
    return d;
}

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolClientCapabilities::Tasks::Requests &t)
{
    d.space() << "sampling:" << t.sampling();
    d.space() << "elicitation:" << t.elicitation();
    return d;
}

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolClientCapabilities::Tasks::Requests::Sampling &t)
{
    d.space() << "createMessage:" << t.createMessage();
    return d;
}

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolClientCapabilities::Tasks::Requests::Elicitation &t)
{
    d.space() << "create:" << t.create();
    return d;
}

McpProtocolClientCapabilities::Elicitation McpProtocolClientCapabilities::Elicitation::fromJson(const QJsonObject &obj)
{
    McpProtocolClientCapabilities::Elicitation elicitation;
    if (obj.contains("form"_L1) && obj["form"_L1].isObject()) {
        const QJsonObject mapObj_form = obj["form"_L1].toObject();
        QMap<QString, QJsonValue> map_form;
        for (auto it = mapObj_form.constBegin(); it != mapObj_form.constEnd(); ++it) {
            map_form.insert(it.key(), it.value());
        }
        elicitation.setForm(map_form);
    }
    if (obj.contains("url"_L1) && obj["url"_L1].isObject()) {
        const QJsonObject mapObj_url = obj["url"_L1].toObject();
        QMap<QString, QJsonValue> map_url;
        for (auto it = mapObj_url.constBegin(); it != mapObj_url.constEnd(); ++it) {
            map_url.insert(it.key(), it.value());
        }
        elicitation.setUrl(map_url);
    }
    return elicitation;
}

QJsonObject McpProtocolClientCapabilities::Elicitation::toJson(const McpProtocolClientCapabilities::Elicitation &elicitation)
{
    QJsonObject obj;
    if (elicitation.form().has_value()) {
        QJsonObject map_form;
        for (auto it = elicitation.form()->constBegin(); it != elicitation.form()->constEnd(); ++it) {
            map_form.insert(it.key(), it.value());
        }
        obj.insert("form"_L1, map_form);
    }
    if (elicitation.url().has_value()) {
        QJsonObject map_url;
        for (auto it = elicitation.url()->constBegin(); it != elicitation.url()->constEnd(); ++it) {
            map_url.insert(it.key(), it.value());
        }
        obj.insert("url"_L1, map_url);
    }
    return obj;
}

McpProtocolClientCapabilities McpProtocolClientCapabilities::fromJson(const QJsonObject &obj)
{
    McpProtocolClientCapabilities modelHint;
    // TODO
    return modelHint;
}

QJsonObject McpProtocolClientCapabilities::toJson(const McpProtocolClientCapabilities &choice)
{
    QJsonObject obj;
    if (choice.elicitation().has_value()) {
        obj.insert("elicitation"_L1, McpProtocolClientCapabilities::Elicitation::toJson(*choice.elicitation()));
    }
    // TODO
    /*
    if (choice._experimental.has_value()) {
        QJsonObject map_experimental;
        for (auto it = data._experimental->constBegin(); it != data._experimental->constEnd(); ++it) {
            map_experimental.insert(it.key(), QJsonValue(it.value()));
        }
        obj.insert("experimental"_L1, map_experimental);
    }
    */
    if (choice.roots().has_value()) {
        obj.insert("roots"_L1, McpProtocolClientCapabilities::Roots::toJson(*choice.roots()));
    }
    if (choice.sampling().has_value()) {
        obj.insert("sampling"_L1, McpProtocolClientCapabilities::Sampling::toJson(*choice.sampling()));
    }
    // TODO
    /*
    if (choice.tasks().has_value()) {
        obj.insert("tasks"_L1, toJson(*choice.tasks()));
    }
    */
    return obj;
}

std::optional<McpProtocolClientCapabilities::Elicitation> McpProtocolClientCapabilities::elicitation() const
{
    return mElicitation;
}

void McpProtocolClientCapabilities::setElicitation(std::optional<Elicitation> newElicitation)
{
    mElicitation = newElicitation;
}

std::optional<McpProtocolClientCapabilities::Roots> McpProtocolClientCapabilities::roots() const
{
    return mRoots;
}

void McpProtocolClientCapabilities::setRoots(std::optional<Roots> newRoots)
{
    mRoots = newRoots;
}

std::optional<McpProtocolClientCapabilities::Sampling> McpProtocolClientCapabilities::sampling() const
{
    return mSampling;
}

void McpProtocolClientCapabilities::setSampling(std::optional<Sampling> newSampling)
{
    mSampling = std::move(newSampling);
}

std::optional<QMap<QString, QJsonObject>> McpProtocolClientCapabilities::experimental() const
{
    return mExperimental;
}

void McpProtocolClientCapabilities::setExperimental(std::optional<QMap<QString, QJsonObject>> newExperimental)
{
    mExperimental = std::move(newExperimental);
}

std::optional<McpProtocolClientCapabilities::Tasks> McpProtocolClientCapabilities::tasks() const
{
    return mTasks;
}

void McpProtocolClientCapabilities::setTasks(std::optional<Tasks> newTasks)
{
    mTasks = std::move(newTasks);
}

std::optional<QMap<QString, QJsonValue>> McpProtocolClientCapabilities::Elicitation::url() const
{
    return mUrl;
}

void McpProtocolClientCapabilities::Elicitation::setUrl(std::optional<QMap<QString, QJsonValue>> newUrl)
{
    mUrl = newUrl;
}

std::optional<QMap<QString, QJsonValue>> McpProtocolClientCapabilities::Elicitation::form() const
{
    return mForm;
}

void McpProtocolClientCapabilities::Elicitation::setForm(std::optional<QMap<QString, QJsonValue>> newForm)
{
    mForm = newForm;
}

McpProtocolClientCapabilities::Roots McpProtocolClientCapabilities::Roots::fromJson(const QJsonObject &obj)
{
    McpProtocolClientCapabilities::Roots roots;
    if (obj.contains("listChanged"_L1)) {
        roots.setListChanged(obj.value("listChanged"_L1).toBool());
    }
    return roots;
}

QJsonObject McpProtocolClientCapabilities::Roots::toJson(const Roots &roots)
{
    QJsonObject obj;
    if (roots.listChanged().has_value()) {
        obj["listChanged"_L1] = *roots.listChanged();
    }
    return obj;
}

std::optional<bool> McpProtocolClientCapabilities::Roots::listChanged() const
{
    return mListChanged;
}

void McpProtocolClientCapabilities::Roots::setListChanged(std::optional<bool> newListChanged)
{
    mListChanged = newListChanged;
}

std::optional<QMap<QString, QJsonValue>> McpProtocolClientCapabilities::Sampling::context() const
{
    return mContext;
}

void McpProtocolClientCapabilities::Sampling::setContext(std::optional<QMap<QString, QJsonValue>> newContext)
{
    mContext = newContext;
}

std::optional<QMap<QString, QJsonValue>> McpProtocolClientCapabilities::Sampling::tools() const
{
    return mTools;
}

void McpProtocolClientCapabilities::Sampling::setTools(std::optional<QMap<QString, QJsonValue>> newTools)
{
    mTools = newTools;
}

McpProtocolClientCapabilities::Sampling McpProtocolClientCapabilities::Sampling::fromJson(const QJsonObject &obj)
{
    McpProtocolClientCapabilities::Sampling sampling;
    if (obj.contains("context"_L1) && obj["context"_L1].isObject()) {
        const QJsonObject mapObj_context = obj["context"_L1].toObject();
        QMap<QString, QJsonValue> map_context;
        for (auto it = mapObj_context.constBegin(); it != mapObj_context.constEnd(); ++it) {
            map_context.insert(it.key(), it.value());
        }
        sampling.setContext(map_context);
    }
    if (obj.contains("tools"_L1) && obj["tools"_L1].isObject()) {
        const QJsonObject mapObj_tools = obj["tools"_L1].toObject();
        QMap<QString, QJsonValue> map_tools;
        for (auto it = mapObj_tools.constBegin(); it != mapObj_tools.constEnd(); ++it) {
            map_tools.insert(it.key(), it.value());
        }
        sampling.setTools(map_tools);
    }
    return sampling;
}

QJsonObject McpProtocolClientCapabilities::Sampling::toJson(const McpProtocolClientCapabilities::Sampling &sampling)
{
    QJsonObject obj;
    if (sampling.context().has_value()) {
        QJsonObject map_context;
        for (auto it = sampling.context()->constBegin(); it != sampling.context()->constEnd(); ++it) {
            map_context.insert(it.key(), it.value());
        }
        obj["context"_L1] = map_context;
    }
    if (sampling.tools().has_value()) {
        QJsonObject map_tools;
        for (auto it = sampling.tools()->constBegin(); it != sampling.tools()->constEnd(); ++it) {
            map_tools.insert(it.key(), it.value());
        }
        obj["tools"_L1] = map_tools;
    }
    return obj;
}

std::optional<McpProtocolClientCapabilities::Tasks::Requests> McpProtocolClientCapabilities::Tasks::requests() const
{
    return mRequests;
}

void McpProtocolClientCapabilities::Tasks::setRequests(std::optional<McpProtocolClientCapabilities::Tasks::Requests> newRequests)
{
    mRequests = newRequests;
}

std::optional<QMap<QString, QJsonValue>> McpProtocolClientCapabilities::Tasks::list() const
{
    return mList;
}

void McpProtocolClientCapabilities::Tasks::setList(std::optional<QMap<QString, QJsonValue>> newList)
{
    mList = newList;
}

std::optional<QMap<QString, QJsonValue>> McpProtocolClientCapabilities::Tasks::cancel() const
{
    return mCancel;
}

void McpProtocolClientCapabilities::Tasks::setCancel(std::optional<QMap<QString, QJsonValue>> newCancel)
{
    mCancel = newCancel;
}

std::optional<QMap<QString, QJsonValue>> McpProtocolClientCapabilities::Tasks::Requests::Elicitation::create() const
{
    return mCreate;
}

void McpProtocolClientCapabilities::Tasks::Requests::Elicitation::setCreate(std::optional<QMap<QString, QJsonValue>> newCreate)
{
    mCreate = newCreate;
}

bool McpProtocolClientCapabilities::Tasks::Requests::Elicitation::operator==(const Elicitation &other) const = default;
McpProtocolClientCapabilities::Tasks::Requests::Elicitation McpProtocolClientCapabilities::Tasks::Requests::Elicitation::fromJson(const QJsonObject &obj)
{
    McpProtocolClientCapabilities::Tasks::Requests::Elicitation elicitation;
    if (obj.contains("create"_L1) && obj["create"_L1].isObject()) {
        const QJsonObject mapObj_create = obj["create"_L1].toObject();
        QMap<QString, QJsonValue> map_create;
        for (auto it = mapObj_create.constBegin(); it != mapObj_create.constEnd(); ++it) {
            map_create.insert(it.key(), it.value());
        }
        elicitation.setCreate(map_create);
    }
    return elicitation;
}

QJsonObject McpProtocolClientCapabilities::Tasks::Requests::Elicitation::toJson(const McpProtocolClientCapabilities::Tasks::Requests::Elicitation &image)
{
    QJsonObject obj;
    if (image.create().has_value()) {
        QJsonObject map_create;
        const auto create = *image.create();
        for (auto it = create.constBegin(); it != create.constEnd(); ++it) {
            map_create.insert(it.key(), it.value());
        }
        obj.insert("create"_L1, map_create);
    }
    return obj;
}

bool McpProtocolClientCapabilities::Tasks::Requests::Sampling::operator==(const Sampling &other) const = default;

McpProtocolClientCapabilities::Tasks::Requests::Sampling McpProtocolClientCapabilities::Tasks::Requests::Sampling::fromJson(const QJsonObject &obj)
{
    McpProtocolClientCapabilities::Tasks::Requests::Sampling sampling;
    if (obj.contains("createMessage"_L1) && obj["createMessage"_L1].isObject()) {
        const QJsonObject mapObj_create = obj["createMessage"_L1].toObject();
        QMap<QString, QJsonValue> map_create;
        for (auto it = mapObj_create.constBegin(); it != mapObj_create.constEnd(); ++it) {
            map_create.insert(it.key(), it.value());
        }
        sampling.setCreateMessage(map_create);
    }
    return sampling;
}
QJsonObject McpProtocolClientCapabilities::Tasks::Requests::Sampling::toJson(const McpProtocolClientCapabilities::Tasks::Requests::Sampling &image)
{
    QJsonObject obj;
    if (image.createMessage().has_value()) {
        QJsonObject map_create;
        const auto create = *image.createMessage();
        for (auto it = create.constBegin(); it != create.constEnd(); ++it) {
            map_create.insert(it.key(), it.value());
        }
        obj.insert("createMessage"_L1, map_create);
    }
    return obj;
}

std::optional<QMap<QString, QJsonValue>> McpProtocolClientCapabilities::Tasks::Requests::Sampling::createMessage() const
{
    return mCreateMessage;
}

void McpProtocolClientCapabilities::Tasks::Requests::Sampling::setCreateMessage(std::optional<QMap<QString, QJsonValue>> newCreateMessage)
{
    mCreateMessage = newCreateMessage;
}

#include "moc_mcpprotocolclientcapabilities.cpp"
