/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolSubscriptionsListenResultMetaObject>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolSubscriptionsListenResult
{
public:
    /*!
     */
    McpProtocolSubscriptionsListenResult();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolSubscriptionsListenResult &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolSubscriptionsListenResult fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolSubscriptionsListenResult &result);

    /*!
     */
    [[nodiscard]] bool isValid() const;

    /*!
     */
    [[nodiscard]] McpProtocolSubscriptionsListenResultMetaObject meta() const;
    /*!
     */
    void setMeta(McpProtocolSubscriptionsListenResultMetaObject newMeta);

private:
    McpProtocolSubscriptionsListenResultMetaObject mMeta;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolSubscriptionsListenResult, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolSubscriptionsListenResult &t);
