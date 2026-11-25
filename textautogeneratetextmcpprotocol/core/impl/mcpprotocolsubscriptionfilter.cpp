/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolsubscriptionfilter.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolSubscriptionFilter::McpProtocolSubscriptionFilter() = default;

bool McpProtocolSubscriptionFilter::operator==(const McpProtocolSubscriptionFilter &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolSubscriptionFilter &t)
{
    d.space() << "toolsListChanged:" << t.toolsListChanged();
    d.space() << "promptsListChanged:" << t.promptsListChanged();
    d.space() << "resourcesListChanged:" << t.resourcesListChanged();
    d.space() << "resourceSubscriptions:" << t.resourceSubscriptions();
    return d;
}

McpProtocolSubscriptionFilter McpProtocolSubscriptionFilter::fromJson(const QJsonObject &obj)
{
    McpProtocolSubscriptionFilter filter;
    if (const QJsonValue toolsListChangedValue = obj.value("toolsListChanged"_L1); toolsListChangedValue.isBool()) {
        filter.setToolsListChanged(toolsListChangedValue.toBool());
    }
    if (const QJsonValue promptsListChangedValue = obj.value("promptsListChanged"_L1); promptsListChangedValue.isBool()) {
        filter.setPromptsListChanged(promptsListChangedValue.toBool());
    }
    if (const QJsonValue resourcesListChangedValue = obj.value("resourcesListChanged"_L1); resourcesListChangedValue.isBool()) {
        filter.setResourcesListChanged(resourcesListChangedValue.toBool());
    }
    if (const QJsonValue resourceSubscriptionsValue = obj.value("resourceSubscriptions"_L1); resourceSubscriptionsValue.isArray()) {
        QStringList resourceSubscriptions;
        const QJsonArray resourceSubscriptionsArray = resourceSubscriptionsValue.toArray();
        for (const QJsonValue &uri : resourceSubscriptionsArray) {
            if (!uri.isString()) {
                qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolSubscriptionFilter: invalid field 'resourceSubscriptions'";
                return {};
            }
            resourceSubscriptions.append(uri.toString());
        }
        filter.setResourceSubscriptions(std::move(resourceSubscriptions));
    }
    return filter;
}

QJsonObject McpProtocolSubscriptionFilter::toJson(const McpProtocolSubscriptionFilter &subscriptionFilter)
{
    QJsonObject obj;
    if (const auto toolsListChanged = subscriptionFilter.toolsListChanged(); toolsListChanged.has_value()) {
        obj["toolsListChanged"_L1] = *toolsListChanged;
    }
    if (const auto promptsListChanged = subscriptionFilter.promptsListChanged(); promptsListChanged.has_value()) {
        obj["promptsListChanged"_L1] = *promptsListChanged;
    }
    if (const auto resourcesListChanged = subscriptionFilter.resourcesListChanged(); resourcesListChanged.has_value()) {
        obj["resourcesListChanged"_L1] = *resourcesListChanged;
    }
    if (const auto resourceSubscriptions = subscriptionFilter.resourceSubscriptions(); resourceSubscriptions.has_value()) {
        obj["resourceSubscriptions"_L1] = QJsonArray::fromStringList(*resourceSubscriptions);
    }
    return obj;
}

std::optional<bool> McpProtocolSubscriptionFilter::toolsListChanged() const
{
    return mToolsListChanged;
}

void McpProtocolSubscriptionFilter::setToolsListChanged(std::optional<bool> newToolsListChanged)
{
    mToolsListChanged = newToolsListChanged;
}

std::optional<bool> McpProtocolSubscriptionFilter::promptsListChanged() const
{
    return mPromptsListChanged;
}

void McpProtocolSubscriptionFilter::setPromptsListChanged(std::optional<bool> newPromptsListChanged)
{
    mPromptsListChanged = newPromptsListChanged;
}

std::optional<bool> McpProtocolSubscriptionFilter::resourcesListChanged() const
{
    return mResourcesListChanged;
}

void McpProtocolSubscriptionFilter::setResourcesListChanged(std::optional<bool> newResourcesListChanged)
{
    mResourcesListChanged = newResourcesListChanged;
}

std::optional<QStringList> McpProtocolSubscriptionFilter::resourceSubscriptions() const
{
    return mResourceSubscriptions;
}

void McpProtocolSubscriptionFilter::setResourceSubscriptions(std::optional<QStringList> newResourceSubscriptions)
{
    mResourceSubscriptions = std::move(newResourceSubscriptions);
}
