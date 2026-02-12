/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QByteArray>
#include <QObject>
namespace TextAutoGenerateText
{
class TextAutoGenerateMessagesModel;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateSearchMessageSettings
 * \brief The TextAutoGenerateSearchMessageSettings class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateSearchMessageSettings
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateSearchMessageSettings : public QObject
{
    Q_OBJECT
public:
    /*!
     * Constructs a new TextAutoGenerateSearchMessageSettings object.
     * \param model The TextAutoGenerateMessagesModel instance
     * \param parent The parent QObject
     */
    explicit TextAutoGenerateSearchMessageSettings(TextAutoGenerateMessagesModel *model, QObject *parent = nullptr);
    /*!
     * Destroys the TextAutoGenerateSearchMessageSettings object.
     */
    ~TextAutoGenerateSearchMessageSettings() override;

    /*!
     * Moves to the next search result.
     */
    void next();
    /*!
     * Moves to the previous search result.
     */
    void previous();

    /*!
     * Returns the identifier of the currently selected search message.
     * \return The current message identifier
     */
    [[nodiscard]] QByteArray currentMessageIdentifier() const;
    /*!
     * Sets the identifier of the currently selected search message.
     * \param newCurrentMessageIdentifier The message identifier to set
     */
    void setCurrentMessageIdentifier(const QByteArray &newCurrentMessageIdentifier);

    /*!
     * Returns the current search result index.
     * \return The index of the current search result
     */
    [[nodiscard]] int currentSearchIndex() const;
    /*!
     * Sets the current search result index.
     * \param newCurrentSearchIndex The index to set
     */
    void setCurrentSearchIndex(int newCurrentSearchIndex);

    /*!
     * Clears the current search state.
     */
    void clear();

    /*!
     * Returns the total number of search results found.
     * \return The count of matching search results
     */
    [[nodiscard]] int foundSearchCount() const;
    /*!
     * Sets the total number of search results found.
     * \param newFoundSearchCount The count to set
     */
    void setFoundSearchCount(int newFoundSearchCount);

Q_SIGNALS:
    /*!
     * Emitted when a search message should be refreshed.
     * \param identifier The ID of the message to refresh
     * \param previousIdentifier The ID of the previously selected message
     * \param index The index of the search result
     */
    void refreshMessage(const QByteArray &identifier, const QByteArray &previousIdentifier, int index);
    /*!
     * Emitted to update the enabled state of navigation buttons.
     * \param nextEnabled Whether the next button should be enabled
     * \param previousEnabled Whether the previous button should be enabled
     */
    void updateNextPreviousButtons(bool nextEnabled, bool previousEnabled);

private:
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT bool canSearchMessage() const;
    TEXTAUTOGENERATETEXT_NO_EXPORT void lastMessageUuid();
    TextAutoGenerateMessagesModel *const mMessageModel;
    QByteArray mCurrentMessageIdentifier;
    int mCurrentSearchIndex = -1;
    int mFoundSearchCount = -1;
};
}
