/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_export.h"
#include <QDebug>
#include <QPointer>
#include <TextAutoGenerateText/TextAutoGenerateMessage>
namespace TextAutoGenerateText
{
class TextAutoGenerateMessagesModel;
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateChat
{
    Q_GADGET
public:
    TextAutoGenerateChat();
    TextAutoGenerateChat(const TextAutoGenerateChat &other);
    TextAutoGenerateChat &operator=(const TextAutoGenerateChat &other);

    ~TextAutoGenerateChat();

    [[nodiscard]] bool favorite() const;
    void setFavorite(bool newFavorite);

    [[nodiscard]] bool archived() const;
    void setArchived(bool newArchived);

    [[nodiscard]] QByteArray identifier() const;
    void setIdentifier(const QByteArray &newIdentifier);

    [[nodiscard]] bool operator==(const TextAutoGenerateChat &other) const;

    [[nodiscard]] QString title() const;
    void setTitle(const QString &newTitle);

    [[nodiscard]] qint64 dateTime() const;

    static QByteArray serialize(const TextAutoGenerateChat &msg, bool toBinary = true);
    [[nodiscard]] static TextAutoGenerateChat deserialize(const QJsonObject &source);

    [[nodiscard]] TextAutoGenerateMessagesModel *messageModel() const;

    [[nodiscard]] bool initialized() const;
    void setInitialized(bool newInitialized);

private:
    QSharedPointer<TextAutoGenerateMessagesModel> mMessageModel;
    QByteArray mIdentifier;
    QString mTitle;
    bool mFavorite = false;
    bool mArchived = false;
    bool mInitialized = false;
};

}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateChat, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateChat &t);
