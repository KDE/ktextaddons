/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

#include "textautogeneratetext_export.h"
#include <QDebug>

#include <QJsonDocument>
#include <TextAutoGenerateText/TextAutoGenerateTextContext>
#include <TextAutoGenerateText/TextAutoGenerateTextReplyInfo>

class QNetworkReply;

/**
 * @brief The OllamaReply class represents a reply from an LLM.
 *
 * If you want to stream a reply as it is written in real time, connect to contentAdded() and use readResponse() to retrieve
 * the new content. If you prefer to wait for the entire reply before displaying anything, connect to finished(), which will
 * only be emitted once the reply is complete.
 */
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateReply : public QObject
{
    Q_OBJECT

public:
    struct DownloadModelInfo {
        quint64 total = 0;
        quint64 completed = 0;
        QString status;
    };

    /**
     * @brief Specifies the request type.
     *
     * When the class in instantiated the type of request should be specified
     */
    enum class RequestTypes : uint8_t {
        Unknown,
        StreamingGenerate,
        StreamingChat,
        Show,
        DownloadModel,
    };
    explicit TextAutoGenerateReply(QNetworkReply *netReply, RequestTypes requestType, QObject *parent = nullptr);
    ~TextAutoGenerateReply() override;

    /**
     * @brief Get the context token for this response.
     *
     * Messages sent by most LLMs have a context identifier that allows you to chain messages into a conversation. To create
     * such a conversation, you need to take this context object and set it on the next KLLMRequest in the conversation.
     * KLLMInterface::getCompletion() will use that context object to continue the message thread.
     *
     * @return A context object that refers to this response.
     */
    const TextAutoGenerateText::TextAutoGenerateTextContext &context() const;

    /**
     * @brief Get extra information about the reply.
     *
     * This function returns a TextAutoGenerateTextReplyInfo object containing information about this reply. If the reply has not finished, the KLLMReplyInfo
     * object will have all members set to their default values.
     *
     * @return Extra information about the reply.
     */
    const TextAutoGenerateText::TextAutoGenerateTextReplyInfo &info() const;

    /**
     * @brief Get request type.
     *
     * The request type is set when this object is created.
     *
     * @return Corresponding request type.
     */
    const TextAutoGenerateText::TextAutoGenerateReply::RequestTypes &requestType() const;

Q_SIGNALS:
    /**
     * @brief Emits when new content has been added to the response.
     *
     * If you are not streaming the response live, this signal is not of importance to you. However, if you are streaming
     * content, when this signal is emitted, you should call readResponse() to update the response that your application
     * shows.
     */
    void contentAdded();

    /**
     * @brief Emits when the LLM has finished returning its response.
     *
     * After this signal has emitted, the content is guaranteed to not change. At this point, you should call readResponse()
     * to get the content and then either take ownership of the KLLMReply or delete it, as automatic reply deletion is not
     * implemented yet.
     */
    void finished();

    void downloadInProgress(const TextAutoGenerateText::TextAutoGenerateReply::DownloadModelInfo &info);

protected:
    QNetworkReply *const mReply;
    QByteArray mIncompleteTokens;

    QList<QJsonDocument> mTokens;

    const RequestTypes mRequestType = RequestTypes::Unknown;
    // TODO context remove it
    TextAutoGenerateText::TextAutoGenerateTextContext mContext;
    TextAutoGenerateText::TextAutoGenerateTextReplyInfo mInfo;

    qint64 mReceivedSize = 0;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateReply::DownloadModelInfo, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateReply::DownloadModelInfo &t);
