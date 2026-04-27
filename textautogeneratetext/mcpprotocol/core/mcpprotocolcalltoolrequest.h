/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolcalltoolrequestparams.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolCallToolRequest
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
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolCallToolRequest, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCallToolRequest &t);
