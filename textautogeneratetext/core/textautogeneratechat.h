/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_export.h"
#include <QSharedPointer>
#include <TextAutoGenerateText/TextAutoGenerateMessage>
class QDebug;
namespace TextAutoGenerateText
{
class TextAutoGenerateMessagesModel;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateChat
 * \brief The TextAutoGenerateChat class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateChat
 */
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

    /*!
     * Constructs a new TextAutoGenerateChat object.
     */
    TextAutoGenerateChat();
    /*!
     * Constructs a copy of the TextAutoGenerateChat object from another object.
     * \param other The TextAutoGenerateChat object to copy from
     */
    TextAutoGenerateChat(const TextAutoGenerateChat &other);
    /*!
     * Assigns the contents of another TextAutoGenerateChat object to this object.
     * \param other The TextAutoGenerateChat object to assign from
     * \return A reference to this TextAutoGenerateChat object
     */
    TextAutoGenerateChat &operator=(const TextAutoGenerateChat &other);

    /*!
     * Destroys the TextAutoGenerateChat object.
     */
    ~TextAutoGenerateChat();

    /*!
     * Returns whether the chat is marked as a favorite.
     * \return true if the chat is a favorite, false otherwise
     */
    [[nodiscard]] bool favorite() const;
    /*!
     * Sets whether the chat is marked as a favorite.
     * \param newFavorite true to mark as favorite, false to unmark
     */
    void setFavorite(bool newFavorite);

    /*!
     * Returns whether the chat is archived.
     * \return true if the chat is archived, false otherwise
     */
    [[nodiscard]] bool archived() const;
    /*!
     * Sets whether the chat is archived.
     * \param newArchived true to archive the chat, false to unarchive
     */
    void setArchived(bool newArchived);

    /*!
     * Returns the unique identifier of the chat.
     * \return The chat identifier as a QByteArray
     */
    [[nodiscard]] QByteArray identifier() const;
    /*!
     * Sets the unique identifier of the chat.
     * \param newIdentifier The identifier to set
     */
    void setIdentifier(const QByteArray &newIdentifier);

    /*!
     * Compares this TextAutoGenerateChat with another object for equality.
     * \param other The TextAutoGenerateChat object to compare with
     * \return true if both objects are equal, false otherwise
     */
    [[nodiscard]] bool operator==(const TextAutoGenerateChat &other) const;

    /*!
     * Returns the title of the chat.
     * \return The chat title as a QString
     */
    [[nodiscard]] QString title() const;
    /*!
     * Sets the title of the chat.
     * \param newTitle The title to set
     */
    void setTitle(const QString &newTitle);

    /*!
     * Returns the date and time of the chat.
     * \return The date/time as a 64-bit integer timestamp
     */
    [[nodiscard]] qint64 dateTime() const;
    /*!
     * Sets the date and time of the chat.
     * \param dt The date/time to set as a 64-bit integer timestamp
     */
    void setDateTime(qint64 dt);

    /*!
     * Serializes the given TextAutoGenerateChat object.
     * \param msg The TextAutoGenerateChat object to serialize
     * \param toBinary true to serialize to binary format, false for JSON format
     * \return The serialized data as a QByteArray
     */
    static QByteArray serialize(const TextAutoGenerateChat &msg, bool toBinary = true);
    /*!
     * Deserializes a TextAutoGenerateChat object from JSON.
     * \param source The JSON object to deserialize from
     * \return The deserialized TextAutoGenerateChat object
     */
    [[nodiscard]] static TextAutoGenerateChat deserialize(const QJsonObject &source);

    /*!
     * Returns the messages model for this chat.
     * \return A pointer to the TextAutoGenerateMessagesModel
     */
    [[nodiscard]] TextAutoGenerateMessagesModel *messageModel() const;

    /*!
     * Returns whether the chat has been initialized.
     * \return true if the chat is initialized, false otherwise
     */
    [[nodiscard]] bool initialized() const;
    /*!
     * Sets the initialization status of the chat.
     * \param newInitialized true to mark the chat as initialized, false otherwise
     */
    void setInitialized(bool newInitialized);

    /*!
     * Returns the section category of the chat in the history.
     * \return The SectionHistory enum value
     */
    [[nodiscard]] TextAutoGenerateChat::SectionHistory section() const;

    /*!
     * Returns whether the chat is currently processing.
     * \return true if the chat is in progress, false otherwise
     */
    [[nodiscard]] bool inProgress() const;
    /*!
     * Sets the in-progress status of the chat.
     * \param newInProgress true if the chat is processing, false otherwise
     */
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
