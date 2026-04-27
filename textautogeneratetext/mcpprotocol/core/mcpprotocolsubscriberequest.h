/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolpaginatedrequestparams.h"
#include "mcpprotocolsubscriberequestparams.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
class QDebug;
class QJsonObject;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolSubscribeRequest
{
public:
    /*!
     */
    McpProtocolSubscribeRequest();
    /*!
     */
    ~McpProtocolSubscribeRequest();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolSubscribeRequest &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolSubscribeRequest fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolSubscribeRequest &image);

    /*!
     */
    [[nodiscard]] McpProtocolUtils::RequestId id() const;
    /*!
     */
    void setId(const McpProtocolUtils::RequestId &newId);

    /*!
     */
    [[nodiscard]] McpProtocolSubscribeRequestParams params() const;
    /*!
     */
    void setParams(const McpProtocolSubscribeRequestParams &newParams);

private:
    McpProtocolUtils::RequestId mId;
    McpProtocolSubscribeRequestParams mParams;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolSubscribeRequest, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolSubscribeRequest &t);
