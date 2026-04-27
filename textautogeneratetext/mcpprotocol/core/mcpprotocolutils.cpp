/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolutils.h"
#include "mcpprotocolaudiocontent.h"
#include "mcpprotocolblobresourcecontents.h"
#include "mcpprotocolcalltoolrequest.h"
#include "mcpprotocolcancellednotification.h"
#include "mcpprotocolcanceltaskrequest.h"
#include "mcpprotocolcompleterequest.h"
#include "mcpprotocolelicitationcompletenotification.h"
#include "mcpprotocolembeddedresource.h"
#include "mcpprotocolgetpromptrequest.h"
#include "mcpprotocolgettaskpayloadrequest.h"
#include "mcpprotocolgettaskrequest.h"
#include "mcpprotocolimagecontent.h"
#include "mcpprotocolinitializednotification.h"
#include "mcpprotocolinitializerequest.h"
#include "mcpprotocollistpromptsrequest.h"
#include "mcpprotocollistresourcesrequest.h"
#include "mcpprotocollistresourcetemplatesrequest.h"
#include "mcpprotocollisttasksrequest.h"
#include "mcpprotocollisttoolsrequest.h"
#include "mcpprotocolloggingmessagenotification.h"
#include "mcpprotocolpingrequest.h"
#include "mcpprotocolprogressnotification.h"
#include "mcpprotocolpromptlistchangednotification.h"
#include "mcpprotocolpromptreference.h"
#include "mcpprotocolreadresourcerequest.h"
#include "mcpprotocolresourcelink.h"
#include "mcpprotocolresourcelistchangednotification.h"
#include "mcpprotocolresourcetemplatereference.h"
#include "mcpprotocolresourceupdatednotification.h"
#include "mcpprotocolrootslistchangednotification.h"
#include "mcpprotocolsetlevelrequest.h"
#include "mcpprotocolsubscriberequest.h"
#include "mcpprotocoltaskstatusnotification.h"
#include "mcpprotocoltextcontent.h"
#include "mcpprotocoltextresourcecontents.h"
#include "mcpprotocoltoollistchangednotification.h"
#include "mcpprotocoltoolresultcontent.h"
#include "mcpprotocoltoolusecontent.h"
#include "mcpprotocolunsubscriberequest.h"
#include "mcpprotocolunsubscriberequestparams.h"

#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonArray>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
QString TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertRoleToString(McpProtocolUtils::Role role)
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

TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::Role TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertRoleFromString(const QString &str)
{
    if (str == "assistant"_L1) {
        return McpProtocolUtils::Role::Assistant;
    } else if (str == "user"_L1) {
        return McpProtocolUtils::Role::User;
    }
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Unknown role name " << str;
    return McpProtocolUtils::Role::Unknown;
}

QString TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertLoggingLevelToString(McpProtocolUtils::LoggingLevel level)
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

TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::LoggingLevel
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertLoggingLevelFromString(const QString &str)
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
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid LoggingLevel: " << str;
    return McpProtocolUtils::LoggingLevel::Unknown;
}

QString TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertTaskStatusToString(McpProtocolUtils::TaskStatus level)
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

TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::TaskStatus
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertTaskStatusFromString(const QString &str)
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
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid TaskStatus: " << str;
        return McpProtocolUtils::TaskStatus::Unknown;
    }
}

TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProgressToken
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::progressTokenFromJson(const QJsonValue &val)
{
    if (val.isString()) {
        return ProgressToken(val.toString());
    }
    if (val.isDouble()) {
        return ProgressToken(val.toInt());
    }
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid requestIdFromJson: " << val;
    return {};
}

TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::RequestId TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::requestIdFromJson(const QJsonValue &val)
{
    if (val.isString()) {
        return RequestId(val.toString());
    }
    if (val.isDouble()) {
        return RequestId(val.toInt());
    }
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid requestIdFromJson: " << val;
    return {};
}

QJsonValue TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::requestIdToJson(const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::RequestId &val)
{
    return QVariant::fromValue(val).toJsonValue();
}

QJsonValue TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::progressTokenToJson(const ProgressToken &val)
{
    return QVariant::fromValue(val).toJsonValue();
}

TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::EmbeddedResourceResource
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::embeddedResourceResourceFromJson(const QJsonValue &val)
{
    if (!val.isObject()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid EmbeddedResourceResource: expected object or array";
        return {};
    }
    const QJsonObject obj = val.toObject();
    if (obj.contains("text"_L1)) {
        return EmbeddedResourceResource(McpProtocolTextResourceContents::fromJson(obj));
    }
    if (obj.contains("blob"_L1)) {
        return EmbeddedResourceResource(McpProtocolBlobResourceContents::fromJson(obj));
    }
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid EmbeddedResourceResource";
    return {};
}

QJsonValue TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::embeddedResourceResourceToJson(
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::EmbeddedResourceResource &val)
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

TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::CompleteRequestParamsRef
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::completeRequestParamsRefFromJson(const QJsonValue &val)
{
    if (!val.isObject()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid CompleteRequestParamsRef: expected object or array";
        return {};
    }
    const QString dispatchValue = val.toObject().value("type"_L1).toString();
    if (dispatchValue == "ref/prompt"_L1) {
        return CompleteRequestParamsRef(McpProtocolPromptReference::fromJson(val.toObject()));
    } else if (dispatchValue == "ref/resource"_L1) {
        return CompleteRequestParamsRef(McpProtocolResourceTemplateReference::fromJson(val.toObject()));
    }
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid CompleteRequestParamsRef: unknown type \"" << dispatchValue << "\"";
    return {};
}

QJsonValue TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::completeRequestParamsRefToJson(const CompleteRequestParamsRef &val)
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

TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ClientNotification
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::clientNotificationFromJson(const QJsonValue &val)
{
    if (!val.isObject()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid ClientNotification: expected object";
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
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid ClientNotification: unknown method \"" << dispatchValue << "\"";
    return {};
}

QJsonValue TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::clientNotificationToJson(
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ClientNotification &val)
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

QString
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::getProgressTokenValue(const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProgressToken &token)
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

#if 0
QString TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::getCompleteRequestParamsRef(const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::CompleteRequestParamsRef &token)
{
    return std::visit(
        [](auto &&arg) -> QString {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, McpProtocolPromptReference>) {
                return arg.name();
            } else if constexpr (std::is_same_v<T, McpProtocolResourceTemplateReference>) {
                return arg.uri();
            }
        },
        token);
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::CompleteRequestParamsRef &t)
{
    d.space() << "t:" << TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::getCompleteRequestParamsRef(t);
    return d;
}
#endif
QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProgressToken &t)
{
    d.space() << "progressToken:" << TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::getProgressTokenValue(t);
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::Role &t)
{
    d.space() << "role:" << TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertRoleToString(t);
    return d;
}

QJsonObject
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::contentBlocktoJson(const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ContentBlock &val)
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

TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ContentBlock
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::contentBlockFromJson(const QJsonValue &val)
{
    if (!val.isObject()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid ContentBlock: expected object";
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
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid ContentBlock: unknown method \"" << dispatchValue << "\"";
    return {};
}

TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ClientRequest
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::clientRequestFromJson(const QJsonValue &val)
{
    if (!val.isObject()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid ClientRequest: expected object";
        return {};
    }
    const QString dispatchValue = val.toObject().value("method"_L1).toString();
    const QJsonObject valObj = val.toObject();
    if (dispatchValue == "initialize"_L1) {
        return ClientRequest(McpProtocolInitializeRequest::fromJson(valObj));
    } else if (dispatchValue == "ping"_L1) {
        return ClientRequest(McpProtocolPingRequest::fromJson(valObj));
    } else if (dispatchValue == "resources/list"_L1) {
        return ClientRequest(McpProtocolListResourcesRequest::fromJson(valObj));
    } else if (dispatchValue == "resources/templates/list"_L1) {
        return ClientRequest(McpProtocolListResourceTemplatesRequest::fromJson(valObj));
    } else if (dispatchValue == "resources/read"_L1) {
        return ClientRequest(McpProtocolReadResourceRequest::fromJson(valObj));
    } else if (dispatchValue == "resources/subscribe"_L1) {
        return ClientRequest(McpProtocolSubscribeRequest::fromJson(valObj));
    } else if (dispatchValue == "resources/unsubscribe"_L1) {
        return ClientRequest(McpProtocolUnsubscribeRequest::fromJson(valObj));
    } else if (dispatchValue == "prompts/list"_L1) {
        return ClientRequest(McpProtocolListPromptsRequest::fromJson(valObj));
    } else if (dispatchValue == "prompts/get"_L1) {
        return ClientRequest(McpProtocolGetPromptRequest::fromJson(valObj));
    } else if (dispatchValue == "tools/list"_L1) {
        return ClientRequest(McpProtocolListToolsRequest::fromJson(valObj));
    } else if (dispatchValue == "tools/call"_L1) {
        return ClientRequest(McpProtocolCallToolRequest::fromJson(valObj));
    } else if (dispatchValue == "tasks/get"_L1) {
        return ClientRequest(McpProtocolGetTaskRequest::fromJson(valObj));
    } else if (dispatchValue == "tasks/result"_L1) {
        return ClientRequest(McpProtocolGetTaskPayloadRequest::fromJson(valObj));
    } else if (dispatchValue == "tasks/cancel"_L1) {
        return ClientRequest(McpProtocolCancelTaskRequest::fromJson(valObj));
    } else if (dispatchValue == "tasks/list"_L1) {
        return ClientRequest(McpProtocolListTasksRequest::fromJson(valObj));
    } else if (dispatchValue == "logging/setLevel"_L1) {
        return ClientRequest(McpProtocolSetLevelRequest::fromJson(valObj));
    } else if (dispatchValue == "completion/complete"_L1) {
        return ClientRequest(McpProtocolCompleteRequest::fromJson(valObj));
    }
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid ClientRequest: unknown method \"" << dispatchValue << "\"";
    return {};
}

QJsonObject
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::clientRequestToJson(const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ClientRequest &val)
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

TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ServerNotification
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::serverNotificationFromJson(const QJsonValue &val)
{
    if (!val.isObject()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid ServerNotification: expected object";
        return {};
    }
    const QJsonObject valObj = val.toObject();
    const QString dispatchValue = val.toObject().value("method"_L1).toString();
    if (dispatchValue == "notifications/cancelled"_L1) {
        return ServerNotification(McpProtocolCancelledNotification::fromJson(valObj));
    } else if (dispatchValue == "notifications/progress"_L1) {
        return ServerNotification(McpProtocolProgressNotification::fromJson(valObj));
    } else if (dispatchValue == "notifications/resources/list_changed"_L1) {
        return ServerNotification(McpProtocolResourceListChangedNotification::fromJson(valObj));
    } else if (dispatchValue == "notifications/resources/updated"_L1) {
        return ServerNotification(McpProtocolResourceUpdatedNotification::fromJson(valObj));
    } else if (dispatchValue == "notifications/prompts/list_changed"_L1) {
        return ServerNotification(McpProtocolPromptListChangedNotification::fromJson(valObj));
    } else if (dispatchValue == "notifications/tools/list_changed"_L1) {
        return ServerNotification(McpProtocolToolListChangedNotification::fromJson(valObj));
    } else if (dispatchValue == "notifications/tasks/status"_L1) {
        return ServerNotification(McpProtocolTaskStatusNotification::fromJson(valObj));
    } else if (dispatchValue == "notifications/message"_L1) {
        return ServerNotification(McpProtocolLoggingMessageNotification::fromJson(valObj));
    } else if (dispatchValue == "notifications/elicitation/complete"_L1) {
        return ServerNotification(McpProtocolElicitationCompleteNotification::fromJson(valObj));
    }

    qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid ServerNotification: unknown method \"" << dispatchValue << "\"";
    return {};
}

QJsonObject TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::serverNotificationToJson(const ServerNotification &val)
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

TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::CreateMessageResultContent
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::createMessageResultContentFromJson(const QJsonValue &val)
{
    if (val.isArray()) {
        QList<SamplingMessageContentBlock> list;
        for (const QJsonValue &v : val.toArray()) {
            list.append(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::samplingMessageContentBlockFromJson(v));
        }
        return CreateMessageResultContent(std::move(list));
    }
    if (!val.isObject()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid CreateMessageResultContent: expected object or array";
    }
    const QString dispatchValue = val.toObject().value("type"_L1).toString();
    const QJsonObject valObj = val.toObject();
    if (dispatchValue == "text"_L1) {
        return CreateMessageResultContent(McpProtocolTextContent::fromJson(valObj));
    } else if (dispatchValue == "image"_L1) {
        return CreateMessageResultContent(McpProtocolImageContent::fromJson(valObj));
    } else if (dispatchValue == "audio"_L1) {
        return CreateMessageResultContent(McpProtocolAudioContent::fromJson(valObj));
    } else if (dispatchValue == "tool_use"_L1) {
        return CreateMessageResultContent(McpProtocolToolUseContent::fromJson(valObj));
    } else if (dispatchValue == "tool_result"_L1) {
        return CreateMessageResultContent(McpProtocolToolResultContent::fromJson(valObj));
    }
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid CreateMessageResultContent: unknown type \"" << dispatchValue << "\"";
    return {};
}

QJsonValue TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::createMessageResultContentToJson(const CreateMessageResultContent &val)
{
    return std::visit(
        [](const auto &v) -> QJsonValue {
            using T = std::decay_t<decltype(v)>;
            if constexpr (std::is_same_v<T, QList<SamplingMessageContentBlock>>) {
                QJsonArray arr;
                for (const auto &item : v) {
                    arr.append(samplingMessageContentBlockToJson(item));
                }
                return arr;
            } else if constexpr (std::is_same_v<T, QJsonObject>) {
                return v;
            } else {
                return T::toJson(v);
            }
        },
        val);
}

TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::SamplingMessageContentBlock
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::samplingMessageContentBlockFromJson(const QJsonValue &val)
{
    if (!val.isObject()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid SamplingMessageContentBlock: expected object";
        return {};
    }
    const QString dispatchValue = val.toObject().value("type"_L1).toString();
    const QJsonObject valObj = val.toObject();
    if (dispatchValue == "text"_L1) {
        return SamplingMessageContentBlock(McpProtocolTextContent::fromJson(valObj));
    } else if (dispatchValue == "image"_L1) {
        return SamplingMessageContentBlock(McpProtocolImageContent::fromJson(valObj));
    } else if (dispatchValue == "audio"_L1) {
        return SamplingMessageContentBlock(McpProtocolAudioContent::fromJson(valObj));
    } else if (dispatchValue == "tool_use"_L1) {
        return SamplingMessageContentBlock(McpProtocolToolUseContent::fromJson(valObj));
    } else if (dispatchValue == "tool_result"_L1) {
        return SamplingMessageContentBlock(McpProtocolToolResultContent::fromJson(valObj));
    }
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid SamplingMessageContentBlock: unknown type \"" << dispatchValue << "\"";
    return {};
}

QJsonObject TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::samplingMessageContentBlockToJson(const SamplingMessageContentBlock &val)
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
