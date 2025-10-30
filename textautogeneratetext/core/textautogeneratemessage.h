/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_export.h"
#include <QDebug>
#include <TextAutoGenerateText/TextAutoGenerateAnswerInfo>
#include <TextAutoGenerateText/TextAutoGenerateAttachment>

namespace TextAutoGenerateText
{
/**
 * @brief The TextAutoGenerateMessage class
 * @author Laurent Montel <montel@kde.org>
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
    Q_FLAGS(MessageState MessageStates)
    Q_DECLARE_FLAGS(MessageStates, MessageState)

    TextAutoGenerateMessage();
    ~TextAutoGenerateMessage();

    [[nodiscard]] QString content() const;
    void setContent(const QString &newContent);

    [[nodiscard]] TextAutoGenerateMessage::Sender sender() const;
    void setSender(TextAutoGenerateMessage::Sender newSender);

    [[nodiscard]] qint64 dateTime() const;
    void setDateTime(qint64 newDateTime);

    [[nodiscard]] bool isValid() const;

    [[nodiscard]] bool inProgress() const;
    void setInProgress(bool newInProgress);

    [[nodiscard]] bool operator==(const TextAutoGenerateMessage &other) const;

    [[nodiscard]] QByteArray uuid() const;
    void setUuid(const QByteArray &newUuid);

    [[nodiscard]] QString htmlGenerated() const;

    [[nodiscard]] QByteArray answerUuid() const;
    void setAnswerUuid(const QByteArray &newAnswerUuid);

    [[nodiscard]] QString dateTimeStr() const;

    [[nodiscard]] bool mouseHover() const;
    void setMouseHover(bool newMouseHover);

    [[nodiscard]] bool editingMode() const;
    void setEditingMode(bool newEditingMode);

    [[nodiscard]] QString modelName() const;
    [[nodiscard]] QString engineName() const;
    [[nodiscard]] QString instanceName() const;
    [[nodiscard]] QList<QByteArray> tools() const;

    [[nodiscard]] static QByteArray serialize(const TextAutoGenerateMessage &msg, bool toBinary = true);
    [[nodiscard]] static TextAutoGenerateMessage deserialize(const QJsonObject &o);

    [[nodiscard]] QString senderToString() const;

    [[nodiscard]] static TextAutoGenerateMessage::Sender senderFromString(const QString &str);

    [[nodiscard]] QJsonObject convertToOllamaChatJson() const;

    [[nodiscard]] const TextAutoGenerateAnswerInfo *messageInfo() const;

    void setMessageInfo(const TextAutoGenerateAnswerInfo &messageInfo);

    [[nodiscard]] const TextAutoGenerateAttachment *messageAttachment() const;
    void setMessageAttachment(const TextAutoGenerateAttachment &newMessageAttachment);

    void generateHtml(const QString &searchText = {}, int hightLightStringIndex = -1);

    [[nodiscard]] int numberOfTextSearched() const;

    [[nodiscard]] bool textToSpeechInProgress() const;
    void setTextToSpeechInProgress(bool newTextToSpeechInProgress);

private:
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT TextAutoGenerateMessage::MessageStates messageStates() const;
    TEXTAUTOGENERATETEXT_NO_EXPORT void setMessageStates(const MessageStates &newMessageStates);
    TEXTAUTOGENERATETEXT_NO_EXPORT void assignMessageStateValue(MessageState type, bool status);
    TEXTAUTOGENERATETEXT_NO_EXPORT bool messageStateValue(MessageState type) const;
    QSharedDataPointer<TextAutoGenerateAnswerInfo> mMessageInfo;
    QSharedDataPointer<TextAutoGenerateAttachment> mMessageAttachment;
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
