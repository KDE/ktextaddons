/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolInitializeRequestParams>
#include <optional>
class QDebug;
class QJsonObject;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolInitializeRequest
{
public:
    /*!
     */
    McpProtocolInitializeRequest();

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
    [[nodiscard]] static QJsonObject toJson(const McpProtocolInitializeRequest &request);

    /*!
     */
    [[nodiscard]] McpProtocolUtils::RequestId id() const;
    /*!
     */
    void setId(const McpProtocolUtils::RequestId &newId);

    /*!
     */
    [[nodiscard]] McpProtocolInitializeRequestParams params() const;
    /*!
     */
    void setParams(McpProtocolInitializeRequestParams newParams);

private:
    McpProtocolUtils::RequestId mId;
    // Required by specification
    McpProtocolInitializeRequestParams mParams;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeRequest, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeRequest &t);
