/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoltoolchoice.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolToolChoice::McpProtocolToolChoice() = default;

bool McpProtocolToolChoice::operator==(const McpProtocolToolChoice &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolToolChoice &t)
{
    d.space() << "mode:" << t.mode();
    return d;
}

McpProtocolToolChoice McpProtocolToolChoice::fromJson(const QJsonObject &obj)
{
    McpProtocolToolChoice result;
    if (obj.contains("mode"_L1) && obj["mode"_L1].isString()) {
        result.setMode(convertModeFromString(obj["mode"_L1].toString()));
    }
    return result;
}

QJsonObject McpProtocolToolChoice::toJson(const McpProtocolToolChoice &choice)
{
    QJsonObject obj;
    if (choice.mode() != McpProtocolToolChoice::Mode::Unknown) {
        obj["mode"_L1] = convertModeToString(choice.mode());
    }
    return obj;
}

McpProtocolToolChoice::Mode McpProtocolToolChoice::mode() const
{
    return mMode;
}

void McpProtocolToolChoice::setMode(Mode newMode)
{
    mMode = newMode;
}

QString McpProtocolToolChoice::convertModeToString(McpProtocolToolChoice::Mode mode)
{
    switch (mode) {
    case Mode::Auto:
        return u"auto"_s;
    case Mode::None:
        return u"none"_s;
    case Mode::Required:
        return u"required"_s;
    case Mode::Unknown:
        return {};
    }
    return {};
}

McpProtocolToolChoice::Mode McpProtocolToolChoice::convertModeFromString(const QString &str)
{
    if (str == "auto"_L1) {
        return McpProtocolToolChoice::Mode::Auto;
    }
    if (str == "none"_L1) {
        return McpProtocolToolChoice::Mode::None;
    }
    if (str == "required"_L1) {
        return McpProtocolToolChoice::Mode::Required;
    }
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid ToolChoice::Mode value: " << str;
    return {};
}

#include "moc_mcpprotocoltoolchoice.cpp"
