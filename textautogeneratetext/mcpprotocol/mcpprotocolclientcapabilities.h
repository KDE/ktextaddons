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
    struct TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT Elicitation {
        [[nodiscard]] bool operator==(const McpProtocolClientCapabilities::Elicitation &other) const;
        [[nodiscard]] static Elicitation fromJson(const QJsonObject &obj);
        [[nodiscard]] static QJsonObject toJson(const Elicitation &image);
        std::optional<QMap<QString, QJsonValue>> mForm;
        std::optional<QMap<QString, QJsonValue>> mUrl;

        [[nodiscard]] std::optional<QMap<QString, QJsonValue>> form() const;
        void setForm(std::optional<QMap<QString, QJsonValue>> newForm);
        [[nodiscard]] std::optional<QMap<QString, QJsonValue>> url() const;
        void setUrl(std::optional<QMap<QString, QJsonValue>> newUrl);
    };

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

    /*!
     */
    [[nodiscard]] std::optional<Elicitation> elicitation() const;
    /*!
     */
    void setElicitation(std::optional<Elicitation> newElicitation);

private:
    std::optional<Elicitation> mElicitation;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolClientCapabilities, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolClientCapabilities &t);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolClientCapabilities::Elicitation &t);
