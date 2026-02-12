/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_export.h"
#include <TextAutoGenerateText/TextAutoGenerateAnswerInfo>
#include <TextAutoGenerateText/TextAutoGenerateAttachments>

class QDebug;
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateMessage
 * \brief The TextAutoGenerateMessage class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateMessage
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateMessage
{
    Q_GADGET
public:
    enum class Sender : uint8_t {
        Unknown,
        User,
        Assistant,
        System,
        Tool,
    };
    Q_ENUM(Sender)

    enum MessageState {
        None = 0,
        HoverHighlight = 1,
        Edited = 2,
        InProgress = 4,
        TextToSpeechInProgress = 8,
    };
    Q_DECLARE_FLAGS(MessageStates, MessageState)
    Q_FLAG(MessageStates)

    /*!
     * Constructs a new TextAutoGenerateMessage object.
     */
    TextAutoGenerateMessage();
    /*!
     * Destroys the TextAutoGenerateMessage object.
     */
    ~TextAutoGenerateMessage();

    /*!
     * Returns the content of the message.
     * \return The message content as a QString
     */
    [[nodiscard]] QString content() const;
    /*!
     * Sets the content of the message.
     * \param newContent The content to set
     */
    void setContent(const QString &newContent);

    /*!
     * Returns the sender type of the message.
     * \return The Sender enum value
     */
    [[nodiscard]] TextAutoGenerateMessage::Sender sender() const;
    /*!
     * Sets the sender type of the message.
     * \param newSender The sender type to set
     */
    void setSender(TextAutoGenerateMessage::Sender newSender);

    /*!
     * Returns the date and time of the message.
     * \return The date/time as a 64-bit integer timestamp
     */
    [[nodiscard]] qint64 dateTime() const;
    /*!
     * Sets the date and time of the message.
     * \param newDateTime The date/time to set as a 64-bit integer timestamp
     */
    void setDateTime(qint64 newDateTime);

    /*!
     * Returns whether the message is valid.
     * \return true if the message is valid, false otherwise
     */
    [[nodiscard]] bool isValid() const;

    /*!
     * Returns whether the message is currently being processed.
     * \return true if in progress, false otherwise
     */
    [[nodiscard]] bool inProgress() const;
    /*!
     * Sets the processing status of the message.
     * \param newInProgress true if in progress, false otherwise
     */
    void setInProgress(bool newInProgress);

    /*!
     * Compares this TextAutoGenerateMessage with another for equality.
     * \param other The TextAutoGenerateMessage to compare with
     * \return true if both messages are equal, false otherwise
     */
    [[nodiscard]] bool operator==(const TextAutoGenerateMessage &other) const;

    /*!
     * Returns the unique identifier of the message.
     * \return The message UUID as a QByteArray
     */
    [[nodiscard]] QByteArray uuid() const;
    /*!
     * Sets the unique identifier of the message.
     * \param newUuid The UUID to set
     */
    void setUuid(const QByteArray &newUuid);

    /*!
     * Returns the generated HTML representation of the message.
     * \return The HTML content as a QString
     */
    [[nodiscard]] QString htmlGenerated() const;

    /*!
     * Returns the UUID of the associated answer message.
     * \return The answer UUID as a QByteArray
     */
    [[nodiscard]] QByteArray answerUuid() const;
    /*!
     * Sets the UUID of the associated answer message.
     * \param newAnswerUuid The answer UUID to set
     */
    void setAnswerUuid(const QByteArray &newAnswerUuid);

    /*!
     * Returns the date and time as a formatted string.
     * \return The formatted date/time as a QString
     */
    [[nodiscard]] QString dateTimeStr() const;

    /*!
     * Returns whether the mouse is hovering over the message.
     * \return true if hovering, false otherwise
     */
    [[nodiscard]] bool mouseHover() const;
    /*!
     * Sets the mouse hover state for the message.
     * \param newMouseHover true if hovering, false otherwise
     */
    void setMouseHover(bool newMouseHover);

    /*!
     * Returns whether the message is in editing mode.
     * \return true if in editing mode, false otherwise
     */
    [[nodiscard]] bool editingMode() const;
    /*!
     * Sets the editing mode for the message.
     * \param newEditingMode true to enable editing mode, false otherwise
     */
    void setEditingMode(bool newEditingMode);

    /*!
     * Returns the name of the model used for this message.
     * \return The model name as a QString
     */
    [[nodiscard]] QString modelName() const;
    /*!
     * Returns the name of the engine used for this message.
     * \return The engine name as a QString
     */
    [[nodiscard]] QString engineName() const;
    /*!
     * Returns the name of the instance used for this message.
     * \return The instance name as a QString
     */
    [[nodiscard]] QString instanceName() const;
    /*!
     * Returns the list of tools available for this message.
     * \return A list of tool names as QByteArray
     */
    [[nodiscard]] QList<QByteArray> tools() const;

    /*!
     * Serializes the given TextAutoGenerateMessage object.
     * \param msg The TextAutoGenerateMessage to serialize
     * \param toBinary true to serialize to binary format, false for JSON format
     * \return The serialized data as a QByteArray
     */
    [[nodiscard]] static QByteArray serialize(const TextAutoGenerateMessage &msg, bool toBinary = true);
    /*!
     * Deserializes a TextAutoGenerateMessage object from JSON.
     * \param o The JSON object to deserialize from
     * \return The deserialized TextAutoGenerateMessage
     */
    [[nodiscard]] static TextAutoGenerateMessage deserialize(const QJsonObject &o);

    /*!
     * Converts the sender type to a string representation.
     * \return The sender type as a QString
     */
    [[nodiscard]] QString senderToString() const;

    /*!
     * Converts a string representation to a Sender enum value.
     * \param str The sender string to convert
     * \return The corresponding Sender enum value
     */
    [[nodiscard]] static TextAutoGenerateMessage::Sender senderFromString(const QString &str);

    /*!
     * Converts the message to Ollama chat JSON format.
     * \return The message as a QJsonObject in Ollama chat format
     */
    [[nodiscard]] QJsonObject convertToOllamaChatJson() const;

    /*!
     * Returns the answer information for this message.
     * \return A pointer to the TextAutoGenerateAnswerInfo
     */
    [[nodiscard]] const TextAutoGenerateAnswerInfo *messageInfo() const;

    /*!
     * Sets the answer information for this message.
     * \param messageInfo The TextAutoGenerateAnswerInfo to set
     */
    void setMessageInfo(const TextAutoGenerateAnswerInfo &messageInfo);

    /*!
     * Returns the attachments for this message.
     * \return A pointer to the TextAutoGenerateAttachments
     */
    [[nodiscard]] const TextAutoGenerateAttachments *messageAttachments() const;
    /*!
     * Sets the attachments for this message.
     * \param newMessageAttachment The TextAutoGenerateAttachments to set
     */
    void setMessageAttachments(const TextAutoGenerateAttachments &newMessageAttachment);

    /*!
     * Generates HTML representation of the message with optional search text highlighting.
     * \param searchText Optional text to search for and highlight
     * \param hightLightStringIndex The index of the highlight position
     */
    void generateHtml(const QString &searchText = {}, int hightLightStringIndex = -1);

    /*!
     * Returns the number of text search matches in the message.
     * \return The number of matches found
     */
    [[nodiscard]] int numberOfTextSearched() const;

    /*!
     * Returns whether text-to-speech synthesis is in progress.
     * \return true if synthesis is in progress, false otherwise
     */
    [[nodiscard]] bool textToSpeechInProgress() const;
    /*!
     * Sets the text-to-speech synthesis progress status.
     * \param newTextToSpeechInProgress true if synthesis is in progress, false otherwise
     */
    void setTextToSpeechInProgress(bool newTextToSpeechInProgress);

private:
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT TextAutoGenerateMessage::MessageStates messageStates() const;
    TEXTAUTOGENERATETEXT_NO_EXPORT void setMessageStates(MessageStates newMessageStates);
    TEXTAUTOGENERATETEXT_NO_EXPORT void assignMessageStateValue(MessageState type, bool status);
    TEXTAUTOGENERATETEXT_NO_EXPORT bool messageStateValue(MessageState type) const;
    QSharedDataPointer<TextAutoGenerateAnswerInfo> mMessageInfo;
    QSharedDataPointer<TextAutoGenerateAttachments> mMessageAttachments;
    QByteArray mAnswerUuid;
    QByteArray mUuid;
    QString mContent;
    QString mHtmlGenerated;
    QString mDateTimeStr;
    TextAutoGenerateMessage::Sender mSender = TextAutoGenerateMessage::Sender::Unknown;
    // TextAutoGenerateMessage::KLLMReplyInfo info;

    MessageStates mMessageStates = MessageStates(MessageState::None);
    int mNumberOfTextSearched = -1;
    qint64 mDateTime = -1;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateMessage, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateMessage &t);
