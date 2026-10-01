/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolutils.h"
#include "mcpprotocolaudiocontent.h"
#include "mcpprotocolblobresourcecontents.h"
#include "mcpprotocolcalltoolrequest.h"
#include "mcpprotocolcalltoolresult.h"
#include "mcpprotocolcancellednotification.h"
#include "mcpprotocolcanceltaskrequest.h"
#include "mcpprotocolcanceltaskresult.h"
#include "mcpprotocolcompleterequest.h"
#include "mcpprotocolcompleteresult.h"
#include "mcpprotocolelicitationcompletenotification.h"
#include "mcpprotocolembeddedresource.h"
#include "mcpprotocolgetpromptrequest.h"
#include "mcpprotocolgetpromptresult.h"
#include "mcpprotocolgettaskpayloadrequest.h"
#include "mcpprotocolgettaskpayloadresult.h"
#include "mcpprotocolgettaskrequest.h"
#include "mcpprotocolgettaskresult.h"
#include "mcpprotocolimagecontent.h"
#include "mcpprotocolinitializednotification.h"
#include "mcpprotocolinitializerequest.h"
#include "mcpprotocolinitializeresult.h"
#include "mcpprotocoljsonrpcerrorresponse.h"
#include "mcpprotocoljsonrpcresultresponse.h"
#include "mcpprotocollistpromptsrequest.h"
#include "mcpprotocollistpromptsresult.h"
#include "mcpprotocollistresourcesrequest.h"
#include "mcpprotocollistresourcesresult.h"
#include "mcpprotocollistresourcetemplatesrequest.h"
#include "mcpprotocollistresourcetemplatesresult.h"
#include "mcpprotocollisttasksrequest.h"
#include "mcpprotocollisttasksresult.h"
#include "mcpprotocollisttoolsrequest.h"
#include "mcpprotocollisttoolsresult.h"
#include "mcpprotocolloggingmessagenotification.h"
#include "mcpprotocolpingrequest.h"
#include "mcpprotocolprogressnotification.h"
#include "mcpprotocolpromptlistchangednotification.h"
#include "mcpprotocolpromptreference.h"
#include "mcpprotocolreadresourcerequest.h"
#include "mcpprotocolreadresourceresult.h"
#include "mcpprotocolresourcelink.h"
#include "mcpprotocolresourcelistchangednotification.h"
#include "mcpprotocolresourcetemplatereference.h"
#include "mcpprotocolresourceupdatednotification.h"
#include "mcpprotocolresult.h"
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

#include "mcpprotocolbooleanschema.h"
#include "mcpprotocolcreatemessageresult.h"
#include "mcpprotocolelicitrequestformparams.h"
#include "mcpprotocolelicitrequesturlparams.h"
#include "mcpprotocolelicitresult.h"
#include "mcpprotocollegacytitledenumschema.h"
#include "mcpprotocollistrootsresult.h"
#include "mcpprotocolnumberschema.h"
#include "mcpprotocolstringschema.h"
#include "mcpprotocoltitledmultiselectenumschema.h"
#include "mcpprotocoltitledsingleselectenumschema.h"
#include "mcpprotocoluntitledmultiselectenumschema.h"
#include "mcpprotocoluntitledsingleselectenumschema.h"

#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonArray>
#include <QJsonObject>
#include <cmath>
#include <limits>
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
    case McpProtocolUtils::LoggingLevel::Debug:
        return u"debug"_s;
    case McpProtocolUtils::LoggingLevel::Info:
        return u"info"_s;
    case McpProtocolUtils::LoggingLevel::Notice:
        return u"notice"_s;
    case McpProtocolUtils::LoggingLevel::Warning:
        return u"warning"_s;
    case McpProtocolUtils::LoggingLevel::Error:
        return u"error"_s;
    case McpProtocolUtils::LoggingLevel::Critical:
        return u"critical"_s;
    case McpProtocolUtils::LoggingLevel::Alert:
        return u"alert"_s;
    case McpProtocolUtils::LoggingLevel::Emergency:
        return u"emergency"_s;
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

QString TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertTaskStatusToString(McpProtocolUtils::TaskStatus status)
{
    switch (status) {
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
        return ProgressToken(val.toInteger());
    }
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid progressTokenFromJson: " << val;
    return {};
}

TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::RequestId TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::requestIdFromJson(const QJsonValue &val)
{
    if (val.isString()) {
        return RequestId(val.toString());
    }
    if (val.isDouble()) {
        return RequestId(val.toInteger());
    }
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid requestIdFromJson: " << val;
    return {};
}

QJsonValue TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::requestIdToJson(const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::RequestId &val)
{
    return std::visit(
        [](const auto &v) -> QJsonValue {
            return QJsonValue(v);
        },
        val);
}

QJsonValue TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::progressTokenToJson(const ProgressToken &val)
{
    return std::visit(
        [](const auto &v) -> QJsonValue {
            return QJsonValue(v);
        },
        val);
}

TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::EmbeddedResourceResource
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::embeddedResourceResourceFromJson(const QJsonValue &val)
{
    if (!val.isObject()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid EmbeddedResourceResource: expected object";
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
            return T::toJson(v);
        },
        val);
}

TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::CompleteRequestParamsRef
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::completeRequestParamsRefFromJson(const QJsonValue &val)
{
    if (!val.isObject()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid CompleteRequestParamsRef: expected object";
        return {};
    }
    const QJsonObject valObj = val.toObject();
    const QString dispatchValue = valObj.value("type"_L1).toString();
    if (dispatchValue == QLatin1StringView(McpProtocolPromptReference::type())) {
        return CompleteRequestParamsRef(McpProtocolPromptReference::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolResourceTemplateReference::type())) {
        return CompleteRequestParamsRef(McpProtocolResourceTemplateReference::fromJson(valObj));
    }
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid CompleteRequestParamsRef: unknown type \"" << dispatchValue << "\"";
    return {};
}

QJsonValue TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::completeRequestParamsRefToJson(const CompleteRequestParamsRef &val)
{
    return std::visit(
        [](const auto &v) -> QJsonValue {
            using T = std::decay_t<decltype(v)>;
            return T::toJson(v);
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
    if (dispatchValue == QLatin1StringView(McpProtocolCancelledNotification::type())) {
        return ClientNotification(McpProtocolCancelledNotification::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolInitializedNotification::type())) {
        return ClientNotification(McpProtocolInitializedNotification::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolProgressNotification::type())) {
        return ClientNotification(McpProtocolProgressNotification::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolTaskStatusNotification::type())) {
        return ClientNotification(McpProtocolTaskStatusNotification::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolRootsListChangedNotification::type())) {
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
            return T::toJson(v);
        },
        val);
}

QString
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::getProgressTokenValue(const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProgressToken &token)
{
    return std::visit(
        [](const auto &arg) -> QString {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, QString>) {
                return arg;
            } else {
                return QString::number(arg);
            }
        },
        token);
}

QJsonValue
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::JSONRPCResponseToJson(const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::JSONRPCResponse &val)
{
    return std::visit(
        [](const auto &v) -> QJsonObject {
            using T = std::decay_t<decltype(v)>;
            return T::toJson(v);
        },
        val);
}

TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::JSONRPCResponse
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::JSONRPCResponseFromJson(const QJsonValue &val)
{
    if (!val.isObject()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid JSONRPCResponse: expected object";
        return {};
    }
    const QJsonObject obj = val.toObject();
    if (obj.contains("result"_L1)) {
        return McpProtocolJSONRPCResultResponse::fromJson(obj);
    }
    if (obj.contains("error"_L1)) {
        return McpProtocolJSONRPCErrorResponse::fromJson(obj);
    }
    return {};
}

QJsonValue
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::serverResultToJson(const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ServerResult &val)
{
    return std::visit(
        [](const auto &v) -> QJsonObject {
            using T = std::decay_t<decltype(v)>;
            return T::toJson(v);
        },
        val);
}

TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ServerResult
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::serverResultFromJson(const QJsonValue &val)
{
    if (!val.isObject()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid ServerResult: expected object";
        return {};
    }
    const QJsonObject obj = val.toObject();
    if (obj.contains("capabilities"_L1)) {
        return McpProtocolInitializeResult::fromJson(obj);
    }
    if (obj.contains("resources"_L1)) {
        return McpProtocolListResourcesResult::fromJson(obj);
    }
    if (obj.contains("resourceTemplates"_L1)) {
        return McpProtocolListResourceTemplatesResult::fromJson(obj);
    }
    if (obj.contains("contents"_L1)) {
        return McpProtocolReadResourceResult::fromJson(obj);
    }
    if (obj.contains("prompts"_L1)) {
        return McpProtocolListPromptsResult::fromJson(obj);
    }
    if (obj.contains("messages"_L1)) {
        return McpProtocolGetPromptResult::fromJson(obj);
    }
    if (obj.contains("tools"_L1)) {
        return McpProtocolListToolsResult::fromJson(obj);
    }
    if (obj.contains("content"_L1)) {
        return McpProtocolCallToolResult::fromJson(obj);
    }
    if (obj.contains("tasks"_L1)) {
        return McpProtocolListTasksResult::fromJson(obj);
    }
    if (obj.contains("completion"_L1)) {
        return McpProtocolCompleteResult::fromJson(obj);
    }
    // The remaining alternatives cannot be told apart by shape: GetTaskResult and
    // CancelTaskResult both carry the Task fields, and GetTaskPayloadResult is a bare
    // Result. Pick the task result when the Task fields are there, otherwise fall back
    // to Result. A caller that knows which request it sent should parse the concrete
    // class directly instead of going through this dispatcher.
    if (obj.contains("taskId"_L1) && obj.contains("status"_L1)) {
        return McpProtocolGetTaskResult::fromJson(obj);
    }
    return McpProtocolResult::fromJson(obj);
}

QString TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::getCompleteRequestParamsRef(
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::CompleteRequestParamsRef &token)
{
    return std::visit(
        [](const auto &arg) -> QString {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, McpProtocolPromptReference>) {
                return arg.name();
            } else if constexpr (std::is_same_v<T, McpProtocolResourceTemplateReference>) {
                return arg.uri();
            } else {
                return {};
            }
        },
        token);
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProgressToken &t)
{
    d.space() << TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::getProgressTokenValue(t);
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::Role &t)
{
    d.space() << TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertRoleToString(t);
    return d;
}

QJsonObject
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::contentBlocktoJson(const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ContentBlock &val)
{
    return std::visit(
        [](const auto &v) -> QJsonObject {
            using T = std::decay_t<decltype(v)>;
            return T::toJson(v);
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
    const QString dispatchValue = valObj.value("type"_L1).toString();
    if (dispatchValue == QLatin1StringView(McpProtocolTextContent::type())) {
        return ContentBlock(McpProtocolTextContent::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolImageContent::type())) {
        return ContentBlock(McpProtocolImageContent::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolAudioContent::type())) {
        return ContentBlock(McpProtocolAudioContent::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolResourceLink::type())) {
        return ContentBlock(McpProtocolResourceLink::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolEmbeddedResource::type())) {
        return ContentBlock(McpProtocolEmbeddedResource::fromJson(valObj));
    }
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid ContentBlock: unknown type \"" << dispatchValue << "\"";
    return {};
}

TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ClientRequest
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::clientRequestFromJson(const QJsonValue &val)
{
    if (!val.isObject()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid ClientRequest: expected object";
        return {};
    }
    const QJsonObject valObj = val.toObject();
    const QString dispatchValue = valObj.value("method"_L1).toString();
    if (dispatchValue == QLatin1StringView(McpProtocolInitializeRequest::type())) {
        return ClientRequest(McpProtocolInitializeRequest::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolPingRequest::type())) {
        return ClientRequest(McpProtocolPingRequest::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolListResourcesRequest::type())) {
        return ClientRequest(McpProtocolListResourcesRequest::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolListResourceTemplatesRequest::type())) {
        return ClientRequest(McpProtocolListResourceTemplatesRequest::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolReadResourceRequest::type())) {
        return ClientRequest(McpProtocolReadResourceRequest::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolSubscribeRequest::type())) {
        return ClientRequest(McpProtocolSubscribeRequest::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolUnsubscribeRequest::type())) {
        return ClientRequest(McpProtocolUnsubscribeRequest::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolListPromptsRequest::type())) {
        return ClientRequest(McpProtocolListPromptsRequest::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolGetPromptRequest::type())) {
        return ClientRequest(McpProtocolGetPromptRequest::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolListToolsRequest::type())) {
        return ClientRequest(McpProtocolListToolsRequest::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolCallToolRequest::type())) {
        return ClientRequest(McpProtocolCallToolRequest::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolGetTaskRequest::type())) {
        return ClientRequest(McpProtocolGetTaskRequest::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolGetTaskPayloadRequest::type())) {
        return ClientRequest(McpProtocolGetTaskPayloadRequest::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolCancelTaskRequest::type())) {
        return ClientRequest(McpProtocolCancelTaskRequest::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolListTasksRequest::type())) {
        return ClientRequest(McpProtocolListTasksRequest::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolSetLevelRequest::type())) {
        return ClientRequest(McpProtocolSetLevelRequest::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolCompleteRequest::type())) {
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
            return T::toJson(v);
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
    const QString dispatchValue = valObj.value("method"_L1).toString();
    if (dispatchValue == QLatin1StringView(McpProtocolCancelledNotification::type())) {
        return ServerNotification(McpProtocolCancelledNotification::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolProgressNotification::type())) {
        return ServerNotification(McpProtocolProgressNotification::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolResourceListChangedNotification::type())) {
        return ServerNotification(McpProtocolResourceListChangedNotification::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolResourceUpdatedNotification::type())) {
        return ServerNotification(McpProtocolResourceUpdatedNotification::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolPromptListChangedNotification::type())) {
        return ServerNotification(McpProtocolPromptListChangedNotification::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolToolListChangedNotification::type())) {
        return ServerNotification(McpProtocolToolListChangedNotification::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolTaskStatusNotification::type())) {
        return ServerNotification(McpProtocolTaskStatusNotification::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolLoggingMessageNotification::type())) {
        return ServerNotification(McpProtocolLoggingMessageNotification::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolElicitationCompleteNotification::type())) {
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
            return T::toJson(v);
        },
        val);
}

TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::CreateMessageResultContent
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::createMessageResultContentFromJson(const QJsonValue &val)
{
    if (val.isArray()) {
        const QJsonArray arr = val.toArray();
        QList<SamplingMessageContentBlock> list;
        list.reserve(arr.count());
        for (const QJsonValue &v : arr) {
            list.append(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::samplingMessageContentBlockFromJson(v));
        }
        return CreateMessageResultContent(std::move(list));
    }
    if (!val.isObject()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid CreateMessageResultContent: expected object or array";
        return CreateMessageResultContent({});
    }
    const QJsonObject valObj = val.toObject();
    const QString dispatchValue = valObj.value("type"_L1).toString();
    if (dispatchValue == QLatin1StringView(McpProtocolTextContent::type())) {
        return CreateMessageResultContent(McpProtocolTextContent::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolImageContent::type())) {
        return CreateMessageResultContent(McpProtocolImageContent::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolAudioContent::type())) {
        return CreateMessageResultContent(McpProtocolAudioContent::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolToolUseContent::type())) {
        return CreateMessageResultContent(McpProtocolToolUseContent::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolToolResultContent::type())) {
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
    const QJsonObject valObj = val.toObject();
    const QString dispatchValue = valObj.value("type"_L1).toString();
    if (dispatchValue == QLatin1StringView(McpProtocolTextContent::type())) {
        return SamplingMessageContentBlock(McpProtocolTextContent::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolImageContent::type())) {
        return SamplingMessageContentBlock(McpProtocolImageContent::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolAudioContent::type())) {
        return SamplingMessageContentBlock(McpProtocolAudioContent::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolToolUseContent::type())) {
        return SamplingMessageContentBlock(McpProtocolToolUseContent::fromJson(valObj));
    } else if (dispatchValue == QLatin1StringView(McpProtocolToolResultContent::type())) {
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
            return T::toJson(v);
        },
        val);
}

QString TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertProtocolVersionToString(
    TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProtocolVersion protocol)
{
    switch (protocol) {
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProtocolVersion::Unknown:
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "convertProtocolVersionToString invalid";
        return {};
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProtocolVersion::V2024_11_05:
        return u"2024-11-05"_s;
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProtocolVersion::V2025_03_26:
        return u"2025-03-26"_s;
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProtocolVersion::V2025_06_18:
        return u"2025-06-18"_s;
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProtocolVersion::V2025_11_25:
        return u"2025-11-25"_s;
    }
    return {};
}

TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProtocolVersion
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertProtocolVersionFromString(const QString &str)
{
    if (str == "2024-11-05"_L1) {
        return TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProtocolVersion::V2024_11_05;
    } else if (str == "2025-03-26"_L1) {
        return TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProtocolVersion::V2025_03_26;
    } else if (str == "2025-06-18"_L1) {
        return TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProtocolVersion::V2025_06_18;
    } else if (str == "2025-11-25"_L1) {
        return TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProtocolVersion::V2025_11_25;
    }
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "convertProtocolVersionFromString invalid: " << str;
    return TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProtocolVersion::Unknown;
}

QJsonValue
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::clientResultToJson(const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ClientResult &val)
{
    return std::visit(
        [](const auto &v) -> QJsonObject {
            using T = std::decay_t<decltype(v)>;
            return T::toJson(v);
        },
        val);
}

TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ClientResult
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::clientResultFromJson(const QJsonValue &val)
{
    if (!val.isObject()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid ClientResult: expected object";
        return {};
    }
    const QJsonObject obj = val.toObject();
    if (obj.contains("action"_L1)) {
        return McpProtocolElicitResult::fromJson(obj);
    }
    if (obj.contains("roots"_L1)) {
        return McpProtocolListRootsResult::fromJson(obj);
    }
    if (obj.contains("model"_L1) && obj.contains("content"_L1)) {
        return McpProtocolCreateMessageResult::fromJson(obj);
    }
    if (obj.contains("tasks"_L1)) {
        return McpProtocolListTasksResult::fromJson(obj);
    }
    if (obj.contains("status"_L1)) {
        return McpProtocolGetTaskResult::fromJson(obj);
    }
    return McpProtocolResult::fromJson(obj);
}

QJsonValue TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::elicitResultContentValueToJson(
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ElicitResultContentValue &val)
{
    return std::visit(
        [](const auto &v) -> QJsonValue {
            using T = std::decay_t<decltype(v)>;
            if constexpr (std::is_same_v<T, QStringList>) {
                return QJsonArray::fromStringList(v);
            } else {
                return QJsonValue(v);
            }
        },
        val);
}

TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ElicitResultContentValue
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::elicitResultContentValueFromJson(const QJsonValue &val)
{
    if (val.isArray()) {
        QStringList list;
        const QJsonArray arr = val.toArray();
        list.reserve(arr.count());
        for (const QJsonValue &v : arr) {
            list.append(v.toString());
        }
        return ElicitResultContentValue(std::move(list));
    }
    if (val.isBool()) {
        return ElicitResultContentValue(val.toBool());
    }
    if (val.isDouble()) {
        const double number = val.toDouble();
        if (std::trunc(number) == number && number >= std::numeric_limits<int>::min() && number <= std::numeric_limits<int>::max()) {
            return ElicitResultContentValue(static_cast<int>(number));
        }
        return ElicitResultContentValue(number);
    }
    if (val.isString()) {
        return ElicitResultContentValue(val.toString());
    }
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid ElicitResultContentValue: " << val;
    return {};
}

QJsonObject TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::elicitResultContentToJson(
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ElicitResultContent &val)
{
    QJsonObject obj;
    for (auto it = val.constBegin(); it != val.constEnd(); ++it) {
        obj.insert(it.key(), elicitResultContentValueToJson(it.value()));
    }
    return obj;
}

TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ElicitResultContent
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::elicitResultContentFromJson(const QJsonObject &obj)
{
    ElicitResultContent content;
    for (auto it = obj.constBegin(); it != obj.constEnd(); ++it) {
        content.insert(it.key(), elicitResultContentValueFromJson(it.value()));
    }
    return content;
}

QJsonValue TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::enumSchemaToJson(const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::EnumSchema &val)
{
    return std::visit(
        [](const auto &v) -> QJsonObject {
            using T = std::decay_t<decltype(v)>;
            return T::toJson(v);
        },
        val);
}

TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::EnumSchema
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::enumSchemaFromJson(const QJsonValue &val)
{
    if (!val.isObject()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid EnumSchema: expected object";
        return {};
    }
    const QJsonObject obj = val.toObject();
    const QString dispatchValue = obj.value("type"_L1).toString();
    if (dispatchValue == "array"_L1) {
        if (obj.value("items"_L1).toObject().contains("anyOf"_L1)) {
            return EnumSchema(McpProtocolTitledMultiSelectEnumSchema::fromJson(obj));
        }
        return EnumSchema(McpProtocolUntitledMultiSelectEnumSchema::fromJson(obj));
    }
    if (dispatchValue == "string"_L1) {
        if (obj.contains("oneOf"_L1)) {
            return EnumSchema(McpProtocolTitledSingleSelectEnumSchema::fromJson(obj));
        }
        if (obj.contains("enumNames"_L1)) {
            return EnumSchema(McpProtocolLegacyTitledEnumSchema::fromJson(obj));
        }
        if (obj.contains("enum"_L1)) {
            return EnumSchema(McpProtocolUntitledSingleSelectEnumSchema::fromJson(obj));
        }
    }
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid EnumSchema: unknown type \"" << dispatchValue << "\"";
    return {};
}

QJsonValue TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::primitiveSchemaDefinitionToJson(
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::PrimitiveSchemaDefinition &val)
{
    return std::visit(
        [](const auto &v) -> QJsonObject {
            using T = std::decay_t<decltype(v)>;
            return T::toJson(v);
        },
        val);
}

TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::PrimitiveSchemaDefinition
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::primitiveSchemaDefinitionFromJson(const QJsonValue &val)
{
    if (!val.isObject()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid PrimitiveSchemaDefinition: expected object";
        return {};
    }
    const QJsonObject obj = val.toObject();
    const QString dispatchValue = obj.value("type"_L1).toString();
    if (dispatchValue == QLatin1StringView(McpProtocolBooleanSchema::type())) {
        return PrimitiveSchemaDefinition(McpProtocolBooleanSchema::fromJson(obj));
    }
    if (dispatchValue == "integer"_L1 || dispatchValue == "number"_L1) {
        return PrimitiveSchemaDefinition(McpProtocolNumberSchema::fromJson(obj));
    }
    if (dispatchValue == "array"_L1) {
        if (obj.value("items"_L1).toObject().contains("anyOf"_L1)) {
            return PrimitiveSchemaDefinition(McpProtocolTitledMultiSelectEnumSchema::fromJson(obj));
        }
        return PrimitiveSchemaDefinition(McpProtocolUntitledMultiSelectEnumSchema::fromJson(obj));
    }
    if (dispatchValue == "string"_L1) {
        if (obj.contains("oneOf"_L1)) {
            return PrimitiveSchemaDefinition(McpProtocolTitledSingleSelectEnumSchema::fromJson(obj));
        }
        if (obj.contains("enumNames"_L1)) {
            return PrimitiveSchemaDefinition(McpProtocolLegacyTitledEnumSchema::fromJson(obj));
        }
        if (obj.contains("enum"_L1)) {
            return PrimitiveSchemaDefinition(McpProtocolUntitledSingleSelectEnumSchema::fromJson(obj));
        }
        return PrimitiveSchemaDefinition(McpProtocolStringSchema::fromJson(obj));
    }
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid PrimitiveSchemaDefinition: unknown type \"" << dispatchValue << "\"";
    return {};
}

QJsonValue TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::elicitRequestParamsToJson(
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ElicitRequestParams &val)
{
    return std::visit(
        [](const auto &v) -> QJsonObject {
            using T = std::decay_t<decltype(v)>;
            return T::toJson(v);
        },
        val);
}

TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ElicitRequestParams
TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::elicitRequestParamsFromJson(const QJsonValue &val)
{
    if (!val.isObject()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid ElicitRequestParams: expected object";
        return {};
    }
    const QJsonObject obj = val.toObject();
    const QString dispatchValue = obj.value("mode"_L1).toString();
    if (dispatchValue == QLatin1StringView(McpProtocolElicitRequestURLParams::mode())) {
        return ElicitRequestParams(McpProtocolElicitRequestURLParams::fromJson(obj));
    }
    if (dispatchValue == QLatin1StringView(McpProtocolElicitRequestFormParams::mode()) || !obj.contains("mode"_L1)) {
        return ElicitRequestParams(McpProtocolElicitRequestFormParams::fromJson(obj));
    }
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid ElicitRequestParams: unknown mode \"" << dispatchValue << "\"";
    return {};
}
