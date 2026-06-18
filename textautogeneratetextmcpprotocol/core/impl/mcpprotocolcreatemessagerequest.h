/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCreateMessageRequestParams>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolCreateMessageRequest
{
public:
    /*!
     */
    McpProtocolCreateMessageRequest();
    /*!
     */
    ~McpProtocolCreateMessageRequest();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    // TODO [[nodiscard]] bool operator==(const McpProtocolCreateMessageRequest &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolCreateMessageRequest fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolCreateMessageRequest &image);

    /*!
     */
    [[nodiscard]] McpProtocolUtils::RequestId id() const;
    /*!
     */
    void setId(const McpProtocolUtils::RequestId &newId);

    /*!
     */
    [[nodiscard]] McpProtocolCreateMessageRequestParams params() const;
    /*!
     */
    void setParams(const McpProtocolCreateMessageRequestParams &newParams);

private:
    McpProtocolUtils::RequestId mId;
    McpProtocolCreateMessageRequestParams mParams;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageRequest, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageRequest &t);
