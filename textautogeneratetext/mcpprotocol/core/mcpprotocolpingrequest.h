/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolgetpromptrequestparams.h"
#include "mcpprotocolnotificationparams.h"
#include "mcpprotocolrequestparams.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
class QDebug;
class QJsonObject;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolPingRequest
{
public:
    /*!
     */
    McpProtocolPingRequest();
    /*!
     */
    ~McpProtocolPingRequest();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolPingRequest &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolPingRequest fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolPingRequest &image);

    /*!
     */
    [[nodiscard]] McpProtocolUtils::RequestId id() const;
    /*!
     */
    void setId(const McpProtocolUtils::RequestId &newId);

    /*!
     */
    std::optional<McpProtocolRequestParams> params() const;
    /*!
     */
    void setParams(std::optional<McpProtocolRequestParams> newParams);

private:
    McpProtocolUtils::RequestId mId;
    std::optional<McpProtocolRequestParams> mParams;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolPingRequest, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolPingRequest &t);
