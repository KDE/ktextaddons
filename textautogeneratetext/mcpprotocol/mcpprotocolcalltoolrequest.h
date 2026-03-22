/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolcalltoolrequestparams.h"
#include "mcpprotocolnotificationparams.h"
#include "mcpprotocolprompt.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QJsonObject>
#include <QString>
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolCallToolRequest
{
public:
    /*!
     */
    McpProtocolCallToolRequest();
    /*!
     */
    ~McpProtocolCallToolRequest();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolCallToolRequest &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolCallToolRequest fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolCallToolRequest &image);

    /*!
     */
    [[nodiscard]] McpProtocolUtils::RequestId id() const;
    /*!
     */
    void setId(const McpProtocolUtils::RequestId &newId);

    /*!
     */
    [[nodiscard]] McpProtocolCallToolRequestParams params() const;
    /*!
     */
    void setParams(const McpProtocolCallToolRequestParams &newParams);

private:
    McpProtocolUtils::RequestId mId;
    McpProtocolCallToolRequestParams mParams;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolCallToolRequest, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolCallToolRequest &t);
