/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolannotations.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QJsonObject>
#include <QString>
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolToolChoice
{
    Q_GADGET
public:
    enum class Mode : uint8_t {
        Auto = 0,
        None,
        Required,
        Unknown,
    };
    Q_ENUM(Mode)

    /*!
     */
    McpProtocolToolChoice();
    /*!
     */
    ~McpProtocolToolChoice();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolToolChoice &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolToolChoice fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolToolChoice &image);

    /*!
     */
    [[nodiscard]] Mode mode() const;
    /*!
     */
    void setMode(Mode newMode);

    /*!
     */
    [[nodiscard]] static QString convertModeToString(McpProtocolToolChoice::Mode mode);

private:
    Mode mMode = Mode::Unknown;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolToolChoice, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolToolChoice &t);
