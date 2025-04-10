/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_export.h"
#include <QDebug>
namespace TextAutogenerateText
{
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

private:
    QString mContent;
    TextAutoGenerateMessage::Sender mSender = TextAutoGenerateMessage::Sender::Unknown;
    qint64 mDateTime = -1;
    bool mInProgress = false;
};
}
Q_DECLARE_TYPEINFO(TextAutogenerateText::TextAutoGenerateMessage, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutogenerateText::TextAutoGenerateMessage &t);
