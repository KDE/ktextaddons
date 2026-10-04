/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QHash>
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateReply>
#include <TextAutoGenerateText/TextAutoGenerateTextToolPlugin>

namespace TextAutoGenerateText
{
class TextAutoGenerateTextToolInternalInterface;
class TextAutoGenerateMcpToolsManager;
class TextAutoGenerateTextToolBaseJob;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateToolCallJob
 * \brief The TextAutoGenerateToolCallJob class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateToolCallJob
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateToolCallJob : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Constructs a new TextAutoGenerateToolCallJob
     * \param chatId The ID of the chat
     * \param uuid The UUID of the tool call
     * \param info The tool call argument information
     * \param parent The parent object
     */
    explicit TextAutoGenerateToolCallJob(const QByteArray &chatId,
                                         const QByteArray &uuid,
                                         const QList<TextAutoGenerateReply::ToolCallArgumentInfo> &info,
                                         QObject *parent = nullptr);
    /*!
     * \brief Destroys the TextAutoGenerateToolCallJob object
     */
    ~TextAutoGenerateToolCallJob() override;
    /*!
     * \brief Starts the tool call job
     */
    void start();

    /*!
     * \brief Returns whether the tool call job can be started
     * \return True if the job can start, false otherwise
     */
    [[nodiscard]] bool canStart() const;

    /*!
     */
    [[nodiscard]] TextAutoGenerateTextToolInternalInterface *textAutoGenerateTextToolInternalInterface() const;
    /*!
     */
    void setTextAutoGenerateTextToolInternalInterface(TextAutoGenerateTextToolInternalInterface *newTextAutoGenerateTextToolInternalInterface);

    /*!
     * Used to call tools of MCP servers
     */
    void setTextAutoGenerateMcpToolsManager(TextAutoGenerateMcpToolsManager *newTextAutoGenerateMcpToolsManager);

Q_SIGNALS:
    /*!
     * \brief Emitted when tool processing is in progress
     * \param str The progress message
     */
    void toolInProgress(const QString &str);
    /*!
     * \brief Emitted when the tool call is finished
     * \param info The result information from the tool
     */
    void finished(const TextAutoGenerateText::TextAutoGenerateTextToolPlugin::TextToolPluginInfo &info);
    /*!
     * \brief Emitted before finished() with result of each tool call (tool call id, result), in order of tool calls
     */
    void toolResults(const QList<QPair<QByteArray, QString>> &results);

private:
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT TextAutoGenerateText::TextAutoGenerateTextToolBaseJob *
    createJob(const TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo &info);
    TEXTAUTOGENERATETEXT_NO_EXPORT void jobFinished(TextAutoGenerateText::TextAutoGenerateTextToolBaseJob *job,
                                                    const QString &content,
                                                    const QByteArray &toolIdentifier,
                                                    const QList<TextAutoGenerateAttachmentUtils::AttachmentElementInfo> &attachments);
    TEXTAUTOGENERATETEXT_NO_EXPORT void emitFinished();
    QList<TextAutoGenerateText::TextAutoGenerateTextToolBaseJob *> mListJob;
    const QByteArray mChatId;
    const QByteArray mMessageUuid;
    const QList<TextAutoGenerateReply::ToolCallArgumentInfo> mInfos;
    QStringList mResult;
    // Result of each tool call (same order as mInfos)
    QList<QPair<QByteArray, QString>> mToolResults;
    QHash<TextAutoGenerateText::TextAutoGenerateTextToolBaseJob *, int> mJobIndex;
    QList<TextAutoGenerateAttachmentUtils::AttachmentElementInfo> mAttachments;
    QByteArray mToolIdentifier;
    TextAutoGenerateTextToolInternalInterface *mTextAutoGenerateTextToolInternalInterface = nullptr;
    TextAutoGenerateMcpToolsManager *mTextAutoGenerateMcpToolsManager = nullptr;
};
}
