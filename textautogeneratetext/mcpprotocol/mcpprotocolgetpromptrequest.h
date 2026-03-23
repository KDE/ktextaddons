/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolgetpromptrequestparams.h"
#include "mcpprotocolnotificationparams.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QJsonObject>
#include <QString>
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolGetPromptRequest
{
public:
    /*!
     */
    McpProtocolGetPromptRequest();
    /*!
     */
    ~McpProtocolGetPromptRequest();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolGetPromptRequest &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolGetPromptRequest fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolGetPromptRequest &image);

    /*!
     */
    [[nodiscard]] McpProtocolUtils::RequestId id() const;
    /*!
     */
    void setId(const McpProtocolUtils::RequestId &newId);

    /*!
     */
    [[nodiscard]] McpProtocolGetPromptRequestParams params() const;
    /*!
     */
    void setParams(const McpProtocolGetPromptRequestParams &newParams);

private:
    McpProtocolUtils::RequestId mId;
    McpProtocolGetPromptRequestParams mParams;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolGetPromptRequest, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolGetPromptRequest &t);
