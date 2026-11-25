/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QStringList>
#include <optional>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolSubscriptionFilter
{
public:
    /*!
     */
    McpProtocolSubscriptionFilter();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolSubscriptionFilter &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolSubscriptionFilter fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolSubscriptionFilter &subscriptionFilter);

    /*!
     */
    [[nodiscard]] std::optional<bool> toolsListChanged() const;
    /*!
     */
    void setToolsListChanged(std::optional<bool> newToolsListChanged);

    /*!
     */
    [[nodiscard]] std::optional<bool> promptsListChanged() const;
    /*!
     */
    void setPromptsListChanged(std::optional<bool> newPromptsListChanged);

    /*!
     */
    [[nodiscard]] std::optional<bool> resourcesListChanged() const;
    /*!
     */
    void setResourcesListChanged(std::optional<bool> newResourcesListChanged);

    /*!
     */
    [[nodiscard]] std::optional<QStringList> resourceSubscriptions() const;
    /*!
     */
    void setResourceSubscriptions(std::optional<QStringList> newResourceSubscriptions);

private:
    std::optional<bool> mToolsListChanged;
    std::optional<bool> mPromptsListChanged;
    std::optional<bool> mResourcesListChanged;
    std::optional<QStringList> mResourceSubscriptions;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolSubscriptionFilter, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolSubscriptionFilter &t);
