/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

#include "textautogeneratetext_export.h"

#include <QJsonDocument>
#include <QNetworkReply>
#include <TextAutoGenerateText/TextAutoGenerateTextReplyInfo>

class QDebug;

/*!
 * \brief The OllamaReply class represents a reply from an LLM.
 *
 * If you want to stream a reply as it is written in real time, connect to contentAdded() and use readResponse() to retrieve
 * the new content. If you prefer to wait for the entire reply before displaying anything, connect to finished(), which will
 * only be emitted once the reply is complete.
 */
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateReply
 * \brief The TextAutoGenerateReply class represents a reply from an LLM.
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateReply
 * \details If you want to stream a reply as it is written in real time, connect to contentAdded() and use readResponse() to retrieve
 * the new content. If you prefer to wait for the entire reply before displaying anything, connect to finished(), which will
 * only be emitted once the reply is complete.
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateReply : public QObject
{
    Q_OBJECT

public:
    struct TEXTAUTOGENERATETEXT_EXPORT ToolCallArgument {
        QString keyTool;
        QString value;
        [[nodiscard]] bool operator==(const ToolCallArgument &other) const;
    };

    struct TEXTAUTOGENERATETEXT_EXPORT ToolCallArgumentInfo {
        QList<ToolCallArgument> toolCallArgument;
        QByteArray toolName;
        int index = -1;
        [[nodiscard]] bool operator==(const ToolCallArgumentInfo &other) const;
    };

    struct TEXTAUTOGENERATETEXT_EXPORT Response {
        QList<ToolCallArgumentInfo> info;
        QString response;
        [[nodiscard]] bool hasToolCallArguments() const;
    };

    struct DownloadModelInfo {
        quint64 total = 0;
        quint64 completed = 0;
        QString status;
        QString error;
    };

    /*!
     * \brief Specifies the request type.
     *
     * When the class in instantiated the type of request should be specified
     */
    enum class RequestTypes : uint8_t {
        Unknown,
        StreamingGenerate,
        StreamingChat,
        ShowModelInfo,
        DownloadModel,
        DeleteModel,
        CreateModel,
    };
    /*!
     * Constructs a new TextAutoGenerateReply object.
     * \param netReply The QNetworkReply from the network request
     * \param requestType The type of request being made
     * \param parent The parent QObject
     */
    explicit TextAutoGenerateReply(QNetworkReply *netReply, RequestTypes requestType, QObject *parent = nullptr);
    /*!
     * Destroys the TextAutoGenerateReply object.
     */
    ~TextAutoGenerateReply() override;

    /*!
     * \brief Get extra information about the reply.
     *
     * This function returns a TextAutoGenerateTextReplyInfo object containing information about this reply. If the reply has not finished, the KLLMReplyInfo
     * object will have all members set to their default values.
     *
     * Returns Extra information about the reply.
     */
    const TextAutoGenerateText::TextAutoGenerateTextReplyInfo &info() const;

    /*!
     * \brief Get request type.
     *
     * The request type is set when this object is created.
     *
     * Returns Corresponding request type.
     */
    const TextAutoGenerateText::TextAutoGenerateReply::RequestTypes &requestType() const;

    /*!
     * Cancels the reply and stops processing.
     */
    void cancel();

    /*!
     * Reads the response from the LLM.
     * \return The Response containing the LLM output
     */
    [[nodiscard]] virtual TextAutoGenerateText::TextAutoGenerateReply::Response readResponse() const = 0;

Q_SIGNALS:
    /*!
     * \brief Emits when new content has been added to the response.
     *
     * If you are not streaming the response live, this signal is not of importance to you. However, if you are streaming
     * content, when this signal is emitted, you should call readResponse() to update the response that your application
     * shows.
     */
    void contentAdded();

    /*!
     * \brief Emits when the LLM has finished returning its response.
     *
     * After this signal has emitted, the content is guaranteed to not change. At this point, you should call readResponse()
     * to get the content and then either take ownership of the KLLMReply or delete it, as automatic reply deletion is not
     * implemented yet.
     */
    void finished();

    /*!
     * Emitted when the reply has been canceled.
     */
    void canceled();

    /*!
     * Emitted when a model download is in progress.
     */
    void downloadInProgress(const TextAutoGenerateText::TextAutoGenerateReply::DownloadModelInfo &info);
    /*!
     * Emitted when a download error occurs.
     */
    void downloadError(const QString &errorStr);

    /*!
     * Emitted when tools need to be called.
     */
    void callTools(const QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument> &toolsArguments, const QString &toolName);

    /*!
     * Emitted when a network error occurs.
     */
    void errorOccurred(QNetworkReply::NetworkError e);

    /*!
     * Emitted when Ollama login is required.
     */
    void needOllamaLogin();

protected:
    [[nodiscard]] QList<ToolCallArgumentInfo> parseToolCallsOllama(const QJsonArray &array) const;
    [[nodiscard]] QList<TextAutoGenerateReply::ToolCallArgumentInfo> parseToolCallsOpenAI(const QJsonArray &array) const;

    QNetworkReply *const mReply;
    QByteArray mIncompleteTokens;

    QList<QJsonDocument> mTokens;

    const RequestTypes mRequestType = RequestTypes::Unknown;
    TextAutoGenerateText::TextAutoGenerateTextReplyInfo mInfo;

    qint64 mReceivedSize = 0;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument, Q_RELOCATABLE_TYPE);
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateReply::DownloadModelInfo, Q_RELOCATABLE_TYPE);
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo, Q_RELOCATABLE_TYPE);
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateReply::Response, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateReply::DownloadModelInfo &t);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument &t);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo &t);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateReply::Response &t);
