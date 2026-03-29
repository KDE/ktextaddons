/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolutils.h"
#include "mcpprotocolaudiocontent.h"
#include "mcpprotocolblobresourcecontents.h"
#include "mcpprotocolcancellednotification.h"
#include "mcpprotocolembeddedresource.h"
#include "mcpprotocolimagecontent.h"
#include "mcpprotocolinitializednotification.h"
#include "mcpprotocolprogressnotification.h"
#include "mcpprotocolresourcelink.h"
#include "mcpprotocolrootslistchangednotification.h"
#include "mcpprotocoltaskstatusnotification.h"
#include "mcpprotocoltextcontent.h"
#include "mcpprotocoltextresourcecontents.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
QString McpProtocol::McpProtocolUtils::convertRoleToString(McpProtocolUtils::Role role)
{
    switch (role) {
    case McpProtocolUtils::Role::Assistant:
        return u"assistant"_s;
    case McpProtocolUtils::Role::User:
        return u"user"_s;
    case McpProtocolUtils::Role::Unknown:
        return {};
    }
    return {};
}

McpProtocol::McpProtocolUtils::Role McpProtocol::McpProtocolUtils::convertRoleFromString(const QString &str)
{
    if (str == "assistant"_L1) {
        return McpProtocolUtils::Role::Assistant;
    } else if (str == "user"_L1) {
        return McpProtocolUtils::Role::User;
    }
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Unknown role name " << str;
    return McpProtocolUtils::Role::Unknown;
}

QString McpProtocol::McpProtocolUtils::convertLoggingLevelToString(McpProtocolUtils::LoggingLevel level)
{
    switch (level) {
    case McpProtocolUtils::LoggingLevel::Alert:
        return u"alert"_s;
    case McpProtocolUtils::LoggingLevel::Critical:
        return u"critical"_s;
    case McpProtocolUtils::LoggingLevel::Debug:
        return u"debug"_s;
    case McpProtocolUtils::LoggingLevel::Emergency:
        return u"emergency"_s;
    case McpProtocolUtils::LoggingLevel::Error:
        return u"error"_s;
    case McpProtocolUtils::LoggingLevel::Info:
        return u"info"_s;
    case McpProtocolUtils::LoggingLevel::Notice:
        return u"notice"_s;
    case McpProtocolUtils::LoggingLevel::Warning:
        return u"warning"_s;
    case McpProtocolUtils::LoggingLevel::Unknown:
        return {};
    }
    return {};
}

McpProtocol::McpProtocolUtils::LoggingLevel McpProtocol::McpProtocolUtils::convertLoggingLevelFromString(const QString &str)
{
    if (str == "alert"_L1) {
        return McpProtocolUtils::LoggingLevel::Alert;
    } else if (str == "critical"_L1) {
        return McpProtocolUtils::LoggingLevel::Critical;
    } else if (str == "debug"_L1) {
        return McpProtocolUtils::LoggingLevel::Debug;
    } else if (str == "emergency"_L1) {
        return McpProtocolUtils::LoggingLevel::Emergency;
    } else if (str == "error"_L1) {
        return McpProtocolUtils::LoggingLevel::Error;
    } else if (str == "info"_L1) {
        return McpProtocolUtils::LoggingLevel::Info;
    } else if (str == "notice"_L1) {
        return McpProtocolUtils::LoggingLevel::Notice;
    } else if (str == "warning"_L1) {
        return McpProtocolUtils::LoggingLevel::Warning;
    }
    return McpProtocolUtils::LoggingLevel::Unknown;
}

QString McpProtocol::McpProtocolUtils::convertTaskStatusToString(McpProtocolUtils::TaskStatus level)
{
    switch (level) {
    case McpProtocolUtils::TaskStatus::Cancelled:
        return u"cancelled"_s;
    case McpProtocolUtils::TaskStatus::Completed:
        return u"completed"_s;
    case McpProtocolUtils::TaskStatus::Failed:
        return u"failed"_s;
    case McpProtocolUtils::TaskStatus::InputRequired:
        return u"input_required"_s;
    case McpProtocolUtils::TaskStatus::Working:
        return u"working"_s;
    case McpProtocolUtils::TaskStatus::Unknown:
        return {};
    }
    return {};
}

McpProtocol::McpProtocolUtils::TaskStatus McpProtocol::McpProtocolUtils::convertTaskStatusFromString(const QString &str)
{
    if (str == "cancelled"_L1) {
        return McpProtocolUtils::TaskStatus::Cancelled;
    } else if (str == "completed"_L1) {
        return McpProtocolUtils::TaskStatus::Completed;
    } else if (str == "failed"_L1) {
        return McpProtocolUtils::TaskStatus::Failed;
    } else if (str == "input_required"_L1) {
        return McpProtocolUtils::TaskStatus::InputRequired;
    } else if (str == "working"_L1) {
        return McpProtocolUtils::TaskStatus::Working;
    } else {
        return McpProtocolUtils::TaskStatus::Unknown;
    }
}

McpProtocol::McpProtocolUtils::ProgressToken McpProtocol::McpProtocolUtils::progressTokenFromJson(const QJsonValue &val)
{
    if (val.isString()) {
        return ProgressToken(val.toString());
    }
    if (val.isDouble()) {
        return ProgressToken(val.toInt());
    }
    return {};
}

McpProtocol::McpProtocolUtils::RequestId McpProtocol::McpProtocolUtils::requestIdFromJson(const QJsonValue &val)
{
    if (val.isString()) {
        return RequestId(val.toString());
    }
    if (val.isDouble()) {
        return RequestId(val.toInt());
    }
    return {};
}

QJsonValue McpProtocol::McpProtocolUtils::requestIdToJson(const McpProtocol::McpProtocolUtils::RequestId &val)
{
    return QVariant::fromValue(val).toJsonValue();
}

QJsonValue McpProtocol::McpProtocolUtils::progressTokenToJson(const ProgressToken &val)
{
    return QVariant::fromValue(val).toJsonValue();
}

McpProtocol::McpProtocolUtils::EmbeddedResourceResource McpProtocol::McpProtocolUtils::embeddedResourceResourceFromJson(const QJsonValue &val)
{
    if (!val.isObject()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Invalid EmbeddedResourceResource: expected object or array";
        return {};
    }
    const QJsonObject obj = val.toObject();
    if (obj.contains("text"_L1)) {
        return EmbeddedResourceResource(McpProtocolTextResourceContents::fromJson(obj));
    }
    if (obj.contains("blob"_L1)) {
        return EmbeddedResourceResource(McpProtocolBlobResourceContents::fromJson(obj));
    }
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Invalid EmbeddedResourceResource";
    return {};
}

QJsonValue McpProtocol::McpProtocolUtils::embeddedResourceResourceToJson(const McpProtocol::McpProtocolUtils::EmbeddedResourceResource &val)
{
    return std::visit(
        [](const auto &v) -> QJsonValue {
            using T = std::decay_t<decltype(v)>;
            if constexpr (std::is_same_v<T, QJsonObject>) {
                return v;
            } else {
                return T::toJson(v);
            }
        },
        val);
}

McpProtocol::McpProtocolUtils::ClientNotification McpProtocol::McpProtocolUtils::clientNotificationFromJson(const QJsonValue &val)
{
    if (!val.isObject()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Invalid ClientNotification: expected object";
        return {};
    }
    const QJsonObject valObj = val.toObject();
    const QString dispatchValue = valObj.value("method"_L1).toString();
    if (dispatchValue == "notifications/cancelled"_L1) {
        return ClientNotification(McpProtocolCancelledNotification::fromJson(valObj));
    } else if (dispatchValue == "notifications/initialized"_L1) {
        return ClientNotification(McpProtocolInitializedNotification::fromJson(valObj));
    } else if (dispatchValue == "notifications/progress"_L1) {
        return ClientNotification(McpProtocolProgressNotification::fromJson(valObj));
    } else if (dispatchValue == "notifications/tasks/status"_L1) {
        return ClientNotification(McpProtocolTaskStatusNotification::fromJson(valObj));
    } else if (dispatchValue == "notifications/roots/list_changed"_L1) {
        return ClientNotification(McpProtocolRootsListChangedNotification::fromJson(valObj));
    }
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Invalid ClientNotification: unknown method \"" << dispatchValue << "\"";
    return {};
}

QJsonValue McpProtocol::McpProtocolUtils::clientNotificationToJson(const McpProtocol::McpProtocolUtils::ClientNotification &val)
{
    return std::visit(
        [](const auto &v) -> QJsonObject {
            using T = std::decay_t<decltype(v)>;
            if constexpr (std::is_same_v<T, QJsonObject>) {
                return v;
            } else {
                return T::toJson(v);
            }
        },
        val);
}

QString McpProtocol::McpProtocolUtils::getProgressTokenValue(const McpProtocol::McpProtocolUtils::ProgressToken &token)
{
    return std::visit(
        [](auto &&arg) -> QString {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, QString>) {
                return arg;
            } else if constexpr (std::is_same_v<T, int>) {
                return QString::number(arg);
            }
        },
        token);
}

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolUtils::ProgressToken &t)
{
    d.space() << "progressToken:" << McpProtocol::McpProtocolUtils::getProgressTokenValue(t);
    return d;
}

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolUtils::Role &t)
{
    d.space() << "role:" << McpProtocol::McpProtocolUtils::convertRoleToString(t);
    return d;
}

QJsonObject McpProtocol::McpProtocolUtils::contentBlocktoJson(const McpProtocol::McpProtocolUtils::ContentBlock &val)
{
    return std::visit(
        [](const auto &v) -> QJsonObject {
            using T = std::decay_t<decltype(v)>;
            if constexpr (std::is_same_v<T, QJsonObject>) {
                return v;
            } else {
                return T::toJson(v);
            }
        },
        val);
}

McpProtocol::McpProtocolUtils::ContentBlock McpProtocol::McpProtocolUtils::contentBlockFromJson(const QJsonValue &val)
{
    if (!val.isObject()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Invalid ContentBlock: expected object";
        return {};
    }

    const QJsonObject valObj = val.toObject();
    const QString dispatchValue = val.toObject().value("type"_L1).toString();
    if (dispatchValue == "text"_L1) {
        return ContentBlock(McpProtocolTextContent::fromJson(valObj));
    } else if (dispatchValue == "image"_L1) {
        return ContentBlock(McpProtocolImageContent::fromJson(valObj));
    } else if (dispatchValue == "audio"_L1) {
        return ContentBlock(McpProtocolAudioContent::fromJson(valObj));
    } else if (dispatchValue == "resource_link"_L1) {
        return ContentBlock(McpProtocolResourceLink::fromJson(valObj));
    } else if (dispatchValue == "resource"_L1) {
        return ContentBlock(McpProtocolEmbeddedResource::fromJson(valObj));
    }
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Invalid ContentBlock: unknown method \"" << dispatchValue << "\"";
    return {};
}
