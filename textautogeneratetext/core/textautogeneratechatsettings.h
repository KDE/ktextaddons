/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QMap>
#include <QString>
class QDebug;
class QJsonObject;
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateChatSettings
 * \brief The TextAutoGenerateChatSettings class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateChatSettings
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateChatSettings
{
public:
    struct TEXTAUTOGENERATETEXT_EXPORT PendingTypedInfo {
        QString text;
        int scrollbarPosition = -1;
        QList<QByteArray> tools;
        [[nodiscard]] bool isValid() const;
        [[nodiscard]] bool hasPendingMessageTyped() const;
        [[nodiscard]] static QJsonObject serialize(const PendingTypedInfo &url);
        [[nodiscard]] static PendingTypedInfo deserialize(const QJsonObject &o);
        [[nodiscard]] bool operator==(const PendingTypedInfo &other) const;
    };
    /*!
     * Constructs a new TextAutoGenerateChatSettings object.
     * \param manager The TextAutoGenerateManager instance
     */
    explicit TextAutoGenerateChatSettings(TextAutoGenerateManager *manager);
    /*!
     * Destroys the TextAutoGenerateChatSettings object.
     */
    ~TextAutoGenerateChatSettings();

    /*!
     * Removes the pending typed information for the given chat ID.
     * \param chatId The ID of the chat to remove
     */
    void remove(const QByteArray &chatId);

    /*!
     * Adds pending typed information for the given chat ID.
     * \param chatId The ID of the chat
     * \param info The pending typed information to add
     */
    void add(const QByteArray &chatId, const PendingTypedInfo &info);

    /*!
     * Returns the pending typed information for the given chat ID.
     * \param chatId The ID of the chat
     * \return The pending typed information
     */
    [[nodiscard]] PendingTypedInfo value(const QByteArray &chatId);

    /*!
     * Returns whether there is a pending typed message for the given chat ID.
     * \param chatId The ID of the chat
     * \return true if there is a pending typed message, false otherwise
     */
    [[nodiscard]] bool hasPendingMessageTyped(const QByteArray &chatId) const;

    /*!
     * Returns whether the pending typed texts are empty.
     * \return true if empty, false otherwise
     */
    [[nodiscard]] bool isEmpty() const;
    /*!
     * Returns the number of pending typed texts.
     * \return The count of pending typed texts
     */
    [[nodiscard]] int count() const;

    /*!
     * Loads the pending typed information for rooms from the configuration.
     */
    void loadRoomPendingTypedInfo();

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void setPendingTypedTexts(const QMap<QByteArray, TextAutoGenerateChatSettings::PendingTypedInfo> &newPendingTypedTexts);
    QMap<QByteArray /*ChatId*/, PendingTypedInfo> mPendingTypedTexts;
    TextAutoGenerateManager *const mManager;
};
}
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateChatSettings::PendingTypedInfo &t);
