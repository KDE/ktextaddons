/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocol_export.h"
#include <QJsonValue>
#include <QString>
class QDebug;
namespace McpProtocol
{
class McpProtocolTextResourceContents;
class McpProtocolBlobResourceContents;
class McpProtocolTextContent;
class McpProtocolImageContent;
class McpProtocolAudioContent;
class McpProtocolResourceLink;
class McpProtocolEmbeddedResource;
class McpProtocolToolUseContent;
class McpProtocolToolResultContent;
class McpProtocolSamplingMessageContentBlock;
class McpProtocolPromptReference;
class McpProtocolResourceTemplateReference;
class McpProtocolInitializeRequest;
class McpProtocolPingRequest;
class McpProtocolListResourcesRequest;
class McpProtocolListResourceTemplatesRequest;
class McpProtocolReadResourceRequest;
class McpProtocolSubscribeRequest;
class McpProtocolUnsubscribeRequest;
class McpProtocolListPromptsRequest;
class McpProtocolGetPromptRequest;
class McpProtocolListToolsRequest;
class McpProtocolCallToolRequest;
class McpProtocolGetTaskRequest;
class McpProtocolGetTaskPayloadRequest;
class McpProtocolCancelTaskRequest;
class McpProtocolListTasksRequest;
class McpProtocolSetLevelRequest;
class McpProtocolCompleteRequest;

class McpProtocolCancelledNotification;
class McpProtocolInitializedNotification;
class McpProtocolProgressNotification;
class McpProtocolTaskStatusNotification;
class McpProtocolRootsListChangedNotification;

class McpProtocolCancelledNotification;
class McpProtocolProgressNotification;
class McpProtocolResourceListChangedNotification;
class McpProtocolResourceUpdatedNotification;
class McpProtocolPromptListChangedNotification;
class McpProtocolToolListChangedNotification;
class McpProtocolTaskStatusNotification;
class McpProtocolLoggingMessageNotification;
class McpProtocolElicitationCompleteNotification;
}
namespace McpProtocol::McpProtocolUtils
{
using RequestId = std::variant<QString, int>;

using ProgressToken = std::variant<QString, int>;

using EmbeddedResourceResource = std::variant<McpProtocolTextResourceContents, McpProtocolBlobResourceContents>;

using CompleteRequestParamsRef = std::variant<McpProtocolPromptReference, McpProtocolResourceTemplateReference>;

using ClientRequest = std::variant<McpProtocolInitializeRequest,
                                   McpProtocolPingRequest,
                                   McpProtocolListResourcesRequest,
                                   McpProtocolListResourceTemplatesRequest,
                                   McpProtocolReadResourceRequest,
                                   McpProtocolSubscribeRequest,
                                   McpProtocolUnsubscribeRequest,
                                   McpProtocolListPromptsRequest,
                                   McpProtocolGetPromptRequest,
                                   McpProtocolListToolsRequest,
                                   McpProtocolCallToolRequest,
                                   McpProtocolGetTaskRequest,
                                   McpProtocolGetTaskPayloadRequest,
                                   McpProtocolCancelTaskRequest,
                                   McpProtocolListTasksRequest,
                                   McpProtocolSetLevelRequest,
                                   McpProtocolCompleteRequest>;

using ContentBlock =
    std::variant<McpProtocolTextContent, McpProtocolImageContent, McpProtocolAudioContent, McpProtocolResourceLink, McpProtocolEmbeddedResource>;

using Cursor = QString;
using ElicitResultContentValue = std::variant<QStringList, QString, int, bool>;
enum class Role : uint8_t {
    Unknown,
    Assistant,
    User,
};

enum class LoggingLevel : uint8_t {
    Alert,
    Critical,
    Debug,
    Emergency,
    Error,
    Info,
    Notice,
    Warning,
    Unknown,
};

enum class TaskStatus : uint8_t {
    Cancelled,
    Completed,
    Failed,
    InputRequired,
    Working,
    Unknown,
};
using ServerNotification = std::variant<McpProtocolCancelledNotification,
                                        McpProtocolProgressNotification,
                                        McpProtocolResourceListChangedNotification,
                                        McpProtocolResourceUpdatedNotification,
                                        McpProtocolPromptListChangedNotification,
                                        McpProtocolToolListChangedNotification,
                                        McpProtocolTaskStatusNotification,
                                        McpProtocolLoggingMessageNotification,
                                        McpProtocolElicitationCompleteNotification>;

using ClientNotification = std::variant<McpProtocolCancelledNotification,
                                        McpProtocolInitializedNotification,
                                        McpProtocolProgressNotification,
                                        McpProtocolTaskStatusNotification,
                                        McpProtocolRootsListChangedNotification>;

using CreateMessageResultContent = std::variant<McpProtocolTextContent,
                                                McpProtocolImageContent,
                                                McpProtocolAudioContent,
                                                McpProtocolToolUseContent,
                                                McpProtocolToolResultContent,
                                                QList<McpProtocolSamplingMessageContentBlock>>;

[[nodiscard]] QString getProgressTokenValue(const McpProtocol::McpProtocolUtils::ProgressToken &token);

[[nodiscard]] ClientNotification clientNotificationFromJson(const QJsonValue &val);
[[nodiscard]] QJsonValue clientNotificationToJson(const ClientNotification &val);

[[nodiscard]] EmbeddedResourceResource embeddedResourceResourceFromJson(const QJsonValue &val);
[[nodiscard]] QJsonValue embeddedResourceResourceToJson(const EmbeddedResourceResource &val);

[[nodiscard]] RequestId requestIdFromJson(const QJsonValue &val);
[[nodiscard]] QJsonValue requestIdToJson(const RequestId &val);

[[nodiscard]] ProgressToken progressTokenFromJson(const QJsonValue &val);
[[nodiscard]] QJsonValue progressTokenToJson(const ProgressToken &val);

[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QString convertRoleToString(McpProtocolUtils::Role role);
[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolUtils::Role convertRoleFromString(const QString &str);

[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QString convertLoggingLevelToString(McpProtocolUtils::LoggingLevel level);
[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolUtils::LoggingLevel convertLoggingLevelFromString(const QString &str);

[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QString convertTaskStatusToString(McpProtocolUtils::TaskStatus level);
[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolUtils::TaskStatus convertTaskStatusFromString(const QString &str);

[[nodiscard]] QJsonObject contentBlocktoJson(const McpProtocol::McpProtocolUtils::ContentBlock &val);
[[nodiscard]] McpProtocol::McpProtocolUtils::ContentBlock contentBlockFromJson(const QJsonValue &val);
[[nodiscard]] QJsonObject clientRequestToJson(const McpProtocol::McpProtocolUtils::ClientRequest &val);
[[nodiscard]] McpProtocol::McpProtocolUtils::ClientRequest clientRequestFromJson(const QJsonValue &val);

[[nodiscard]] QJsonObject serverNotificationToJson(const ServerNotification &val);
[[nodiscard]] McpProtocol::McpProtocolUtils::ServerNotification serverNotificationFromJson(const QJsonValue &val);
};
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolUtils::ProgressToken &t);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolUtils::Role &t);
// TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolUtils::CompleteRequestParamsRef &t);
