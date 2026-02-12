/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_export.h"
#include <QAbstractListModel>
#include <TextAutoGenerateText/TextAutoGenerateAttachmentUtils>
#include <TextAutoGenerateText/TextAutoGenerateMessage>
namespace TextAutoGenerateText
{
class TextAutoGenerateSearchMessageSettings;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateMessagesModel
 * \brief The TextAutoGenerateMessagesModel class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateMessagesModel
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateMessagesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum MessageRoles : uint16_t {
        MessageHtmlGeneratedRole = Qt::UserRole + 1,
        SenderRole,
        FinishedRole,
        DateTimeRole,
        DateTimeStrRole,
        UuidRole,
        MouseHoverRole,
        EditingRole,
        WaitingAnswerRole,
        ModelInfoRole,
        OriginalMessageRole,
        MessagePointer,
        ToolsRole,
        AnswerUuidRole,
        TextToSpeechInProgressRole,
    };

    /*!
     * Constructs a new TextAutoGenerateMessagesModel object.
     * \param parent The parent QObject
     */
    explicit TextAutoGenerateMessagesModel(QObject *parent = nullptr);
    /*!
     * Destroys the TextAutoGenerateMessagesModel object.
     */
    ~TextAutoGenerateMessagesModel() override;

    /*!
     * Returns the number of messages in the model.
     * \return The row count
     */
    [[nodiscard]] int rowCount(const QModelIndex & = {}) const override;
    /*!
     * Returns the data for the given index and role.
     * \param index The model index
     * \param role The data role
     * \return The data value
     */
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
    /*!
     * Sets the data for the given index and role.
     * \param index The model index
     * \param value The value to set
     * \param role The data role
     * \return true if successful, false otherwise
     */
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    /*!
     * Returns all messages in the model.
     * \return The list of messages
     */
    [[nodiscard]] QList<TextAutoGenerateMessage> messages() const;
    /*!
     * Sets the messages in the model.
     * \param newMessages The messages to set
     */
    void setMessages(const QList<TextAutoGenerateMessage> &newMessages);

    /*!
     * Returns the message with the given UUID.
     * \param uuid The message identifier
     * \return The message or an empty message if not found
     */
    [[nodiscard]] TextAutoGenerateMessage message(const QByteArray &uuid) const;

    /*!
     * Refreshes the answer at the given UUID.
     * \param uuid The message identifier
     * \return The model index of the refreshed message
     */
    [[nodiscard]] QModelIndex refreshAnswer(const QByteArray &uuid) const;

    /*!
     * Resets the conversation, clearing all messages.
     */
    void resetConversation();

    /*!
     * Adds a message to the model.
     * \param msg The message to add
     */
    void addMessage(const TextAutoGenerateMessage &msg);

    /*!
     * Removes a discussion thread starting from the given message UUID.
     * \param uuid The UUID of the message to remove
     * \return List of removed message UUIDs
     */
    [[nodiscard]] QList<QByteArray> removeDiscussion(const QByteArray &uuid);

    /*!
     * Changes the text-to-speech progress state for a message.
     * \param uuid The message identifier
     * \param inProgress true if text-to-speech is in progress, false otherwise
     */
    void changeTextToSpeechInProgress(const QByteArray &uuid, bool inProgress);
    /*!
     * Replaces the content of a message.
     * \param uuid The message identifier
     * \param content The new content
     * \param attachementInfoList List of attachment information
     */
    void
    replaceContent(const QByteArray &uuid, const QString &content, const QList<TextAutoGenerateAttachmentUtils::AttachmentElementInfo> &attachementInfoList);
    /*!
     * Changes the in-progress state for a message.
     * \param uuid The message identifier
     * \param inProgress true if in progress, false otherwise
     */
    void changeInProgress(const QByteArray &uuid, bool inProgress);
    /*!
     * Edits a message with the given content.
     * \param uuid The message identifier
     * \param str The new content
     * \return The UUID of the edited message
     */
    [[nodiscard]] QByteArray editMessage(const QByteArray &uuid, const QString &str);
    /*!
     * Returns the model index for a message with the given UUID.
     * \param uuid The message identifier
     * \return The model index or an invalid index if not found
     */
    [[nodiscard]] QModelIndex indexForUuid(const QByteArray &uuid) const;
    /*!
     * Cancels a request at the given index.
     * \param index The model index
     * \return true if canceled successfully, false otherwise
     */
    [[nodiscard]] bool cancelRequest(const QModelIndex &index);

    /*!
     * Returns the chat identifier.
     * \return The chat ID
     */
    [[nodiscard]] QByteArray chatId() const;
    /*!
     * Sets the chat identifier.
     * \param newChatId The chat ID to set
     */
    void setChatId(const QByteArray &newChatId);

    /*!
     * Converts the messages to Ollama chat format.
     * \return List of messages in JSON object format
     */
    [[nodiscard]] QList<QJsonObject> convertToOllamaChat() const;

    /*!
     * Returns the current search text.
     * \return The search text
     */
    [[nodiscard]] QString searchText() const;
    /*!
     * Sets the search text and returns the number of matching messages.
     * \param newSearchText The search text to set
     * \return The number of messages matching the search text
     */
    [[nodiscard]] int setSearchText(const QString &newSearchText);

    /*!
     * Returns whether the model is empty.
     * \return true if empty, false otherwise
     */
    [[nodiscard]] bool isEmpty() const;

    /*!
     * Finds the last message before the given ID that matches the predicate.
     * \param messageId The reference message ID
     * \param predicate The filtering predicate
     * \return The matching message or an empty message if not found
     */
    [[nodiscard]] TextAutoGenerateMessage findLastMessageBefore(const QByteArray &messageId,
                                                                const std::function<bool(const TextAutoGenerateMessage &)> &predicate) const;
    /*!
     * Finds the next message after the given ID that matches the predicate.
     * \param messageId The reference message ID
     * \param predicate The filtering predicate
     * \return The matching message or an empty message if not found
     */
    [[nodiscard]] TextAutoGenerateMessage findNextMessageAfter(const QByteArray &messageId,
                                                               const std::function<bool(const TextAutoGenerateMessage &)> &predicate) const;
    /*!
     * Returns the search message settings.
     * \return The TextAutoGenerateSearchMessageSettings instance
     */
    [[nodiscard]] TextAutoGenerateSearchMessageSettings *searchMessageSettings() const;

    /*!
     * Regenerates the HTML representation of a message.
     * \param identifier The message identifier
     * \param index The index of the message
     */
    void regenerateHtmlMessage(const QByteArray &identifier, int index);

    /*!
     * Returns the UUID of the last message.
     * \return The UUID or empty if no messages
     */
    [[nodiscard]] QByteArray lastMessageUuid() const;

    /*!
     * Refreshes the colors of all messages in the model.
     */
    void refreshMessageColors();

Q_SIGNALS:
    /*!
     * Emitted when the conversation is cleared.
     */
    void conversationCleared();

private:
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT QList<TextAutoGenerateMessage>::iterator findMessage(const QByteArray &messageId);
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT QList<TextAutoGenerateMessage>::const_iterator findMessage(const QByteArray &messageId) const;

    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT bool waitingAnswer(const TextAutoGenerateMessage &message) const;
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT QString generateModelInfo(const TextAutoGenerateMessage &m) const;
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT int updateAllGeneratedMessages();
    QList<TextAutoGenerateMessage> mMessages;
    QString mSearchText;
    QByteArray mChatId;
    TextAutoGenerateSearchMessageSettings *const mSearchMessageSettings;
};
}
