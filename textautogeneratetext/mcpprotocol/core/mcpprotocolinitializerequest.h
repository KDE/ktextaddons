/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolinitializerequestparams.h"
#include "mcpprotocolpaginatedrequestparams.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
class QDebug;
class QJsonObject;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolInitializeRequest
{
public:
    /*!
     */
    McpProtocolInitializeRequest();
    /*!
     */
    ~McpProtocolInitializeRequest();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolInitializeRequest &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolInitializeRequest fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolInitializeRequest &image);

    /*!
     */
    [[nodiscard]] McpProtocolUtils::RequestId id() const;
    /*!
     */
    void setId(const McpProtocolUtils::RequestId &newId);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolInitializeRequestParams> params() const;
    /*!
     */
    void setParams(std::optional<McpProtocolInitializeRequestParams> newParams);

private:
    McpProtocolUtils::RequestId mId;
    std::optional<McpProtocolInitializeRequestParams> mParams;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolInitializeRequest, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolInitializeRequest &t);
