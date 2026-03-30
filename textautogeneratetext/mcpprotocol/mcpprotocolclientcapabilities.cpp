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
    // TODO
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
    return modelHint;
}

QJsonObject McpProtocolClientCapabilities::toJson(const McpProtocolClientCapabilities &choice)
{
    QJsonObject obj;
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

McpProtocolClientCapabilities::Sampling fromJson(const QJsonObject &obj)
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

QJsonObject toJson(const McpProtocolClientCapabilities::Sampling &sampling)
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

#include "moc_mcpprotocolclientcapabilities.cpp"
