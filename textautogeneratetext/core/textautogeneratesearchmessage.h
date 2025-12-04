/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QObject>
class QDebug;
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateSearchMessage
{
public:
    TextAutoGenerateSearchMessage();
    ~TextAutoGenerateSearchMessage();
    [[nodiscard]] QByteArray chatId() const;
    void setChatId(const QByteArray &newChatId);

    [[nodiscard]] QByteArray messageId() const;
    void setMessageId(const QByteArray &newMessageId);

    [[nodiscard]] QString previewText() const;
    void setPreviewText(const QString &newPreviewText);

    [[nodiscard]] qint64 dateTime() const;
    void setDateTime(qint64 newDateTime);

    [[nodiscard]] bool operator==(const TextAutoGenerateSearchMessage &other) const;

private:
    QString mPreviewText;
    QByteArray mChatId;
    QByteArray mMessageId;
    qint64 mDateTime = -1;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateSearchMessage, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateSearchMessage &t);
