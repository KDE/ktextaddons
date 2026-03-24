/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolcompleterequestparams.h"
#include "mcpprotocolpaginatedrequestparams.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QJsonObject>
#include <QString>
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolCompleteRequest
{
public:
    /*!
     */
    McpProtocolCompleteRequest();
    /*!
     */
    ~McpProtocolCompleteRequest();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolCompleteRequest &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolCompleteRequest fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolCompleteRequest &image);

    /*!
     */
    [[nodiscard]] McpProtocolUtils::RequestId id() const;
    /*!
     */
    void setId(const McpProtocolUtils::RequestId &newId);

    McpProtocolCompleteRequestParams params() const;
    void setParams(const McpProtocolCompleteRequestParams &newParams);

private:
    McpProtocolUtils::RequestId mId;
    McpProtocolCompleteRequestParams mParams;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolCompleteRequest, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolCompleteRequest &t);
