/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_export.h"
#include <QJsonArray>
#include <QObject>
#include <QPointer>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCreateMessageRequest>

namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolCreateMessageResult;
}

namespace TextAutoGenerateText
{
class TextAutoGenerateReply;
class TextAutoGenerateTextPlugin;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateMcpSamplingJob
 * \brief Sends a sampling request of a MCP server to LLM and returns generated message.
 * Job is deleted when finished.
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateMcpSamplingJob : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateMcpSamplingJob(TextAutoGenerateTextPlugin *plugin, QObject *parent = nullptr);
    ~TextAutoGenerateMcpSamplingJob() override;

    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageRequest request() const;
    void setRequest(const TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageRequest &newRequest);

    void start();

    /*!
     * Convert messages of sampling request to LLM messages ({"role":..., "content":...}).
     * System prompt is added as system message when \a systemMessageSupport is true, otherwise before first message.
     * Returns empty array when there is no message or when a message is not a text.
     */
    [[nodiscard]] static QJsonArray convertMessages(const TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageRequestParams &params,
                                                    bool systemMessageSupport);

Q_SIGNALS:
    void finished(const TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageResult &result);
    void failed(const QString &errorString);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void emitFailed(const QString &errorString);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotReplyFinished();
    QPointer<TextAutoGenerateTextPlugin> mPlugin;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageRequest mRequest;
    TextAutoGenerateReply *mReply = nullptr;
    QString mModel;
    QString mErrorString;
};
}
