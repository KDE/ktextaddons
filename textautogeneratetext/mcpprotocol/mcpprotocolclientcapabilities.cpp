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

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolClientCapabilities::Roots &t)
{
    d.space() << "listChanged:" << t.listChanged();
    return d;
}

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolClientCapabilities &t)
{
    d.space() << "elicitation:" << t.elicitation();
    // TODO
    return d;
}

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolClientCapabilities::Elicitation &t)
{
    d.space() << "form:" << t.form();
    d.space() << "url:" << t.url();
    return d;
}

McpProtocolClientCapabilities::Elicitation McpProtocolClientCapabilities::Elicitation::fromJson(const QJsonObject &obj)
{
    McpProtocolClientCapabilities::Elicitation modelHint;
    // TODO
    return modelHint;
}

QJsonObject McpProtocolClientCapabilities::Elicitation::toJson(const McpProtocolClientCapabilities::Elicitation &choice)
{
    QJsonObject obj;
    // TODO
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
    // TODO
    return roots;
}

QJsonObject McpProtocolClientCapabilities::Roots::toJson(const Roots &image)
{
    QJsonObject obj;
    // TODO
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

#include "moc_mcpprotocolclientcapabilities.cpp"
