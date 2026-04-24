/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolmodelpreferences.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolModelPreferences::McpProtocolModelPreferences() = default;

McpProtocolModelPreferences::~McpProtocolModelPreferences() = default;

bool McpProtocolModelPreferences::operator==(const McpProtocolModelPreferences &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolModelPreferences &t)
{
    d.space() << "costPriority:" << t.costPriority();
    d.space() << "hints:" << t.hints();
    d.space() << "intelligencePriority:" << t.intelligencePriority();
    d.space() << "speedPriority:" << t.speedPriority();
    return d;
}

McpProtocolModelPreferences McpProtocolModelPreferences::fromJson(const QJsonObject &obj)
{
    McpProtocolModelPreferences result;
    if (obj.contains("costPriority"_L1)) {
        result.setCostPriority(obj.value("costPriority"_L1).toDouble());
    }
    if (obj.contains("hints"_L1) && obj["hints"_L1].isArray()) {
        const QJsonArray arr = obj["hints"_L1].toArray();
        QList<McpProtocolModelHint> hints;
        for (const QJsonValue &v : arr) {
            hints.append(McpProtocolModelHint::fromJson(v.toObject()));
        }
        result.setHints(hints);
    }
    if (obj.contains("intelligencePriority"_L1)) {
        result.setIntelligencePriority(obj.value("intelligencePriority"_L1).toDouble());
    }
    if (obj.contains("speedPriority"_L1)) {
        result.setSpeedPriority(obj.value("speedPriority"_L1).toDouble());
    }
    return result;
}

QJsonObject McpProtocolModelPreferences::toJson(const McpProtocolModelPreferences &preferences)
{
    QJsonObject obj;
    if (preferences.costPriority().has_value()) {
        obj["costPriority"_L1] = *preferences.costPriority();
    }
    if (preferences.hints().has_value()) {
        QJsonArray hints;
        const auto prefs = *preferences.hints();
        for (const auto &v : prefs) {
            hints.append(McpProtocolModelHint::toJson(v));
        }
        obj["hints"_L1] = hints;
    }
    if (preferences.intelligencePriority().has_value()) {
        obj["intelligencePriority"_L1] = *preferences.intelligencePriority();
    }
    if (preferences.speedPriority().has_value()) {
        obj["speedPriority"_L1] = *preferences.speedPriority();
    }
    return obj;
}

std::optional<double> McpProtocolModelPreferences::costPriority() const
{
    return mCostPriority;
}

void McpProtocolModelPreferences::setCostPriority(std::optional<double> newCostPriority)
{
    mCostPriority = newCostPriority;
}

std::optional<QList<McpProtocolModelHint>> McpProtocolModelPreferences::hints() const
{
    return mHints;
}

void McpProtocolModelPreferences::setHints(std::optional<QList<McpProtocolModelHint>> newHints)
{
    mHints = std::move(newHints);
}

std::optional<double> McpProtocolModelPreferences::intelligencePriority() const
{
    return mIntelligencePriority;
}

void McpProtocolModelPreferences::setIntelligencePriority(std::optional<double> newIntelligencePriority)
{
    mIntelligencePriority = newIntelligencePriority;
}

std::optional<double> McpProtocolModelPreferences::speedPriority() const
{
    return mSpeedPriority;
}

void McpProtocolModelPreferences::setSpeedPriority(std::optional<double> newSpeedPriority)
{
    mSpeedPriority = std::move(newSpeedPriority);
}
