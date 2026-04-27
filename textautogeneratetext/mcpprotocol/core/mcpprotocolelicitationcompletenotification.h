/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
class QDebug;
class QJsonObject;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolElicitationCompleteNotification
{
public:
    struct TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT Params {
        QString mElicitationId;
        [[nodiscard]] Params &elicitationId(const QString &v);
        [[nodiscard]] const QString &elicitationId() const;
        [[nodiscard]] bool operator==(const McpProtocolElicitationCompleteNotification::Params &other) const;
        [[nodiscard]] static Params fromJson(const QJsonObject &obj);
        [[nodiscard]] static QJsonObject toJson(const Params &image);
    };

    /*!
     */
    McpProtocolElicitationCompleteNotification();
    /*!
     */
    ~McpProtocolElicitationCompleteNotification();

    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolElicitationCompleteNotification &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolElicitationCompleteNotification fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolElicitationCompleteNotification &image);

    /*!
     */
    [[nodiscard]] Params params() const;
    /*!
     */
    void setParams(const Params &newParams);

private:
    Params mParams;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolElicitationCompleteNotification, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolElicitationCompleteNotification &t);
