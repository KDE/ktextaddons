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
class TextAutoGenerateMessagesModel;
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateChat
{
    Q_GADGET
public:
    enum class SectionHistory : uint8_t {
        Favorite,
        Today,
        LessThanSevenDays,
        LessThanThirtyDays,
        Later,
        Unknown,
        NSections,
    };
    Q_ENUM(SectionHistory)

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
    void setDateTime(qint64 dt);

    static QByteArray serialize(const TextAutoGenerateChat &msg, bool toBinary = true);
    [[nodiscard]] static TextAutoGenerateChat deserialize(const QJsonObject &source);

    [[nodiscard]] TextAutoGenerateMessagesModel *messageModel() const;

    [[nodiscard]] bool initialized() const;
    void setInitialized(bool newInitialized);

    [[nodiscard]] TextAutoGenerateChat::SectionHistory section() const;

    [[nodiscard]] bool inProgress() const;
    void setInProgress(bool newInProgress);

private:
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT TextAutoGenerateChat::SectionHistory sectionMessage(qint64 dt) const;

    QSharedPointer<TextAutoGenerateMessagesModel> mMessageModel;
    QByteArray mIdentifier;
    QString mTitle;
    qint64 mDateTime = -1;
    bool mFavorite = false;
    bool mArchived = false;
    bool mInitialized = false;
    bool mInProgress = false;
};

}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateChat, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateChat &t);
