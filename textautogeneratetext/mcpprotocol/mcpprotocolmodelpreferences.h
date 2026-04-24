/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolannotations.h"
#include "mcpprotocolmodelhint.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QString>
class QJsonObject;
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolModelPreferences
{
public:
    /*!
     */
    McpProtocolModelPreferences();
    /*!
     */
    ~McpProtocolModelPreferences();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolModelPreferences &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolModelPreferences fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolModelPreferences &image);

    /*!
     */
    [[nodiscard]] std::optional<double> costPriority() const;
    /*!
     */
    void setCostPriority(std::optional<double> newCostPriority);

    /*!
     */
    [[nodiscard]] std::optional<QList<McpProtocolModelHint>> hints() const;
    /*!
     */
    void setHints(std::optional<QList<McpProtocolModelHint>> newHints);

    /*!
     */
    [[nodiscard]] std::optional<double> intelligencePriority() const;
    /*!
     */
    void setIntelligencePriority(std::optional<double> newIntelligencePriority);

    /*!
     */
    [[nodiscard]] std::optional<double> speedPriority() const;
    /*!
     */
    void setSpeedPriority(std::optional<double> newSpeedPriority);

private:
    std::optional<double> mCostPriority;
    std::optional<QList<McpProtocolModelHint>> mHints;
    std::optional<double> mIntelligencePriority;
    std::optional<double> mSpeedPriority;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolModelPreferences, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolModelPreferences &t);
