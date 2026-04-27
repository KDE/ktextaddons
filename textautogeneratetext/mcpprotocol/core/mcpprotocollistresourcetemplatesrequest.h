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
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolListResourceTemplatesRequest
{
public:
    /*!
     */
    McpProtocolListResourceTemplatesRequest();
    /*!
     */
    ~McpProtocolListResourceTemplatesRequest();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolListResourceTemplatesRequest &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolListResourceTemplatesRequest fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolListResourceTemplatesRequest &image);

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
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolListResourceTemplatesRequest, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolListResourceTemplatesRequest &t);
