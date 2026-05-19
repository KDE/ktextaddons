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
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolJSONRPCErrorResponse
{
public:
    /*!
     */
    McpProtocolJSONRPCErrorResponse();
    /*!
     */
    ~McpProtocolJSONRPCErrorResponse();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolJSONRPCErrorResponse &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolJSONRPCErrorResponse fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolJSONRPCErrorResponse &image);

    /*!
     */
    [[nodiscard]] McpProtocolError error() const;
    /*!
     */
    void setError(const McpProtocolError &newError);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolUtils::RequestId> id() const;
    /*!
     */
    void setId(std::optional<McpProtocolUtils::RequestId> newId);

private:
    McpProtocolError mError;
    std::optional<McpProtocolUtils::RequestId> mId;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolJSONRPCErrorResponse, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolJSONRPCErrorResponse &t);
