/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QWidget>
#include <TextAutoGenerateText/TextAutoGenerateAttachmentUtils>

namespace TextAddonsWidgets
{
class QuickSearchBarWidget;
}

namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TextAutoGenerateListView;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateResultWidget
 * \brief The TextAutoGenerateResultWidget class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateResultWidget
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateResultWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Constructor for TextAutoGenerateResultWidget
     * \param manager The TextAutoGenerateManager instance
     * \param parent The parent widget
     */
    explicit TextAutoGenerateResultWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    /*!
     * \brief Destructor for TextAutoGenerateResultWidget
     */
    ~TextAutoGenerateResultWidget() override;

    /*!
     * \brief Handles key press events
     * \param ev The key event to handle
     */
    void handleKeyPressEvent(QKeyEvent *ev);
    /*!
     * \brief Notifies that editing is finished
     * \param uuid The UUID of the message being edited
     */
    void editingFinished(const QByteArray &uuid);

    /*!
     * \brief Returns the current scrollbar position
     * \return The scrollbar position value
     */
    [[nodiscard]] int scrollbarPosition() const;
    /*!
     * \brief Sets the scrollbar position
     * \param position The position to set
     */
    void setScrollbarPosition(int position);
    /*!
     * \brief Scrolls the view to the bottom
     */
    void scrollToBottom();

    /*!
     * \brief Returns the maximum scrollbar position
     * \return The maximum scrollbar position
     */
    [[nodiscard]] int scrollbarPositionMaximum() const;

    /*!
     * \brief Enables or disables quick search text functionality
     * \param enabled Whether to enable or disable quick search
     */
    void quickSearchText(bool enabled);
Q_SIGNALS:
    /*!
     * \brief Emitted when a message needs to be edited
     * \param index The model index of the message
     * \param tools The list of available tools
     */
    void editMessageRequested(const QModelIndex &index, const QList<QByteArray> &tools);
    /*!
     * \brief Emitted when a message generation should be cancelled
     * \param uuid The UUID of the message to cancel
     */
    void cancelRequested(const QByteArray &uuid);
    /*!
     * \brief Emitted when an answer needs to be refreshed
     * \param charId The chat ID
     * \param indexAnswer The model index of the answer
     * \param tools The list of available tools
     * \param attachmentInfoList The list of attachment information
     */
    void refreshAnswerRequested(const QByteArray &charId,
                                const QModelIndex &indexAnswer,
                                const QList<QByteArray> &tools,
                                const QList<TextAutoGenerateText::TextAutoGenerateAttachmentUtils::AttachmentElementInfo> &attachmentInfoList);
    /*!
     * \brief Emitted when switching to a different chat
     * \param uuid The UUID of the chat to switch to
     */
    void switchToChat(const QByteArray &uuid);
    /*!
     * \brief Emitted when the search bar should be closed
     */
    void closeSearchBarRequested();

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotFindNext();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotFindPrev();
    TextAutoGenerateListView *const mTextAutoGenerateListView;
    TextAddonsWidgets::QuickSearchBarWidget *const mQuickSearchBarWidget;
};

}
