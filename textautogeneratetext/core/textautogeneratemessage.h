/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_export.h"
#include <QDebug>
namespace TextAutogenerateText
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
        LLM,
    };
    Q_ENUM(Sender)

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

    [[nodiscard]] QString topic() const;
    void setTopic(const QString &newTopic);

    [[nodiscard]] QString dateTimeStr() const;

    [[nodiscard]] bool mouseHover() const;
    void setMouseHover(bool newMouseHover);

    [[nodiscard]] bool archived() const;
    void setArchived(bool newArchived);

    [[nodiscard]] bool editingMode() const;
    void setEditingMode(bool newEditingMode);

    [[nodiscard]] QString modelInfo() const;
    void setModelInfo(const QString &newModelInfo);

private:
    QByteArray mAnswerUuid;
    QByteArray mUuid;
    QString mContent;
    QString mHtmlGenerated;
    QString mTopic;
    QString mDateTimeStr;
    QString mModelInfo;
    TextAutoGenerateMessage::Sender mSender = TextAutoGenerateMessage::Sender::Unknown;
    qint64 mDateTime = -1;
    bool mInProgress = false;
    bool mMouseHover = false;
    bool mArchived = false;
    bool mEditingMode = false;
};
}
Q_DECLARE_TYPEINFO(TextAutogenerateText::TextAutoGenerateMessage, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutogenerateText::TextAutoGenerateMessage &t);
