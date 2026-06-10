/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolError>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolJSONRPCNotification
{
public:
    /*!
     */
    McpProtocolJSONRPCNotification();
    /*!
     */
    ~McpProtocolJSONRPCNotification();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolJSONRPCNotification &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolJSONRPCNotification fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolJSONRPCNotification &image);

    /*!
     */
    [[nodiscard]] QString method() const;
    /*!
     */
    void setMethod(const QString &newMethod);

    /*!
     */
    [[nodiscard]] std::optional<QMap<QString, QJsonValue>> params() const;
    /*!
     */
    void setParams(std::optional<QMap<QString, QJsonValue>> newParams);

private:
    QString mMethod;
    std::optional<QMap<QString, QJsonValue>> mParams;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolJSONRPCNotification, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolJSONRPCNotification &t);
