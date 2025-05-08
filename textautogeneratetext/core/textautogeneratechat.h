/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_export.h"
#include <QDebug>
#include <TextAutoGenerateText/TextAutoGenerateMessage>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateChat
{
    Q_GADGET
public:
    TextAutoGenerateChat();
    ~TextAutoGenerateChat();

    [[nodiscard]] bool favorite() const;
    void setFavorite(bool newFavorite);

    [[nodiscard]] bool archived() const;
    void setArchived(bool newArchived);

    [[nodiscard]] QByteArray identifier() const;
    void setIdentifier(const QByteArray &newIdentifier);

    [[nodiscard]] bool operator==(const TextAutoGenerateChat &other) const;

    [[nodiscard]] QList<TextAutoGenerateText::TextAutoGenerateMessage> messages() const;
    void setMessages(const QList<TextAutoGenerateText::TextAutoGenerateMessage> &newMessages);

private:
    QList<TextAutoGenerateText::TextAutoGenerateMessage> mMessages;
    QByteArray mIdentifier;
    bool mFavorite = false;
    bool mArchived = false;
};

}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateChat, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateChat &t);
