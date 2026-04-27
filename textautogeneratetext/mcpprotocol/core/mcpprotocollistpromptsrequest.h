/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolpaginatedrequestparams.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
class QJsonObject;
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolListPromptsRequest
{
public:
    /*!
     */
    McpProtocolListPromptsRequest();
    /*!
     */
    ~McpProtocolListPromptsRequest();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolListPromptsRequest &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolListPromptsRequest fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolListPromptsRequest &image);

    /*!
     */
    [[nodiscard]] McpProtocolUtils::RequestId id() const;
    /*!
     */
    void setId(const McpProtocolUtils::RequestId &newId);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolPaginatedRequestParams> params() const;
    /*!
     */
    void setParams(std::optional<McpProtocolPaginatedRequestParams> newParams);

private:
    McpProtocolUtils::RequestId mId;
    std::optional<McpProtocolPaginatedRequestParams> mParams;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolListPromptsRequest, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolListPromptsRequest &t);
