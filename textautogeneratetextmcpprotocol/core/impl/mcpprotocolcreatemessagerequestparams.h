/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolModelPreferences>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolSamplingMessage>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolTaskMetadata>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolTool>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolChoice>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolCreateMessageRequestParams
{
public:
    enum class IncludeContext {
        allServers,
        none,
        thisServer
    };
    struct Meta {
        std::optional<McpProtocolUtils::ProgressToken> mProgressToken;

        [[nodiscard]] std::optional<McpProtocolUtils::ProgressToken> progressToken() const;
        void setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken);
        [[nodiscard]] bool operator==(const McpProtocolCreateMessageRequestParams::Meta &other) const;

        /*!
         */
        [[nodiscard]] static McpProtocolCreateMessageRequestParams::Meta fromJson(const QJsonObject &obj);
        /*!
         */
        [[nodiscard]] static QJsonObject toJson(const McpProtocolCreateMessageRequestParams::Meta &image);
    };

    /*!
     */
    McpProtocolCreateMessageRequestParams();
    /*!
     */
    ~McpProtocolCreateMessageRequestParams();

    /*!
     */
    // TODO [[nodiscard]] bool operator==(const McpProtocolCreateMessageRequestParams &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolCreateMessageRequestParams fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolCreateMessageRequestParams &image);

    /*!
     */
    [[nodiscard]] std::optional<Meta> meta() const;
    /*!
     */
    void setMeta(std::optional<Meta> newMeta);

    /*!
     */
    [[nodiscard]] std::optional<IncludeContext> includeContext() const;
    /*!
     */
    void setIncludeContext(std::optional<IncludeContext> newIncludeContext);

    /*!
     */
    [[nodiscard]] int maxTokens() const;
    /*!
     */
    void setMaxTokens(int newMaxTokens);

    /*!
     */
    [[nodiscard]] std::optional<QMap<QString, QJsonValue>> metadata() const;
    /*!
     */
    void setMetadata(std::optional<QMap<QString, QJsonValue>> newMetadata);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolModelPreferences> modelPreferences() const;
    /*!
     */
    void setModelPreferences(std::optional<McpProtocolModelPreferences> newModelPreferences);

    /*!
     */
    [[nodiscard]] QList<McpProtocolSamplingMessage> messages() const;
    /*!
     */
    void setMessages(const QList<McpProtocolSamplingMessage> &newMessages);

    /*!
     */
    [[nodiscard]] std::optional<QStringList> stopSequences() const;
    /*!
     */
    void setStopSequences(std::optional<QStringList> newStopSequences);

    /*!
     */
    [[nodiscard]] std::optional<QString> systemPrompt() const;
    /*!
     */
    void setSystemPrompt(std::optional<QString> newSystemPrompt);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolTaskMetadata> task() const;
    /*!
     */
    void setTask(std::optional<McpProtocolTaskMetadata> newTask);

    /*!
     */
    [[nodiscard]] std::optional<double> temperature() const;
    /*!
     */
    void setTemperature(std::optional<double> newTemperature);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolToolChoice> toolChoice() const;
    /*!
     */
    void setToolChoice(std::optional<McpProtocolToolChoice> newToolChoice);

    /*!
     */
    [[nodiscard]] std::optional<QList<McpProtocolTool>> tools() const;
    /*!
     */
    void setTools(std::optional<QList<McpProtocolTool>> newTools);

private:
    std::optional<IncludeContext> mIncludeContext;
    int mMaxTokens;
    std::optional<QMap<QString, QJsonValue>> mMetadata;
    std::optional<McpProtocolModelPreferences> mModelPreferences;
    QList<McpProtocolSamplingMessage> mMessages;
    std::optional<QStringList> mStopSequences;
    std::optional<QString> mSystemPrompt;
    std::optional<McpProtocolTaskMetadata> mTask;
    std::optional<double> mTemperature;
    std::optional<McpProtocolToolChoice> mToolChoice;
    std::optional<QList<McpProtocolTool>> mTools;
    std::optional<Meta> mMeta;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageRequestParams, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageRequestParams &t);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d,
                                                             const TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageRequestParams::Meta &t);
