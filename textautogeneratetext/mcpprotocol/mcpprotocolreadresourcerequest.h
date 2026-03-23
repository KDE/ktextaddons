/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolreadresourcerequestparams.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QJsonObject>
#include <QString>
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolReadResourceRequest
{
public:
    /*!
     */
    McpProtocolReadResourceRequest();
    /*!
     */
    ~McpProtocolReadResourceRequest();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolReadResourceRequest &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolReadResourceRequest fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolReadResourceRequest &image);

    /*!
     */
    [[nodiscard]] McpProtocolUtils::RequestId id() const;
    /*!
     */
    void setId(const McpProtocolUtils::RequestId &newId);

    /*!
     */
    [[nodiscard]] McpProtocolReadResourceRequestParams params() const;
    /*!
     */
    void setParams(const McpProtocolReadResourceRequestParams &newParams);

private:
    McpProtocolUtils::RequestId mId;
    McpProtocolReadResourceRequestParams mParams;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolReadResourceRequest, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolReadResourceRequest &t);
