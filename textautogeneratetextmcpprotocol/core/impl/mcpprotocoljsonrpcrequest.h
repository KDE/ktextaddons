/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolJSONRPCRequest
{
public:
    /*!
     */
    McpProtocolJSONRPCRequest();
    /*!
     */
    ~McpProtocolJSONRPCRequest();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolJSONRPCRequest &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolJSONRPCRequest fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolJSONRPCRequest &image);

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

    /*!
     */
    [[nodiscard]] McpProtocolUtils::RequestId id() const;
    /*!
     */
    void setId(const McpProtocolUtils::RequestId &newId);

private:
    McpProtocolUtils::RequestId mId;
    QString mMethod;
    std::optional<QMap<QString, QJsonValue>> mParams;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolJSONRPCRequest, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolJSONRPCRequest &t);
