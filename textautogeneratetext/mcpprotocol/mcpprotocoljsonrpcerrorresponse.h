/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolerror.h"
#include "mcpprotocolnotificationparams.h"
#include "mcpprotocolprompt.h"
#include "mcpprotocoltaskmetadata.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QString>
class QJsonObject;
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolJSONRPCErrorResponse
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
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolJSONRPCErrorResponse, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolJSONRPCErrorResponse &t);
