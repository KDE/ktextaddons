/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QJsonObject>
#include <QString>
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolClientCapabilities
{
    Q_GADGET
public:
    /*!
     */
    McpProtocolClientCapabilities();
    /*!
     */
    ~McpProtocolClientCapabilities();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolClientCapabilities &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolClientCapabilities fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolClientCapabilities &image);

private:
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolClientCapabilities, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolClientCapabilities &t);
