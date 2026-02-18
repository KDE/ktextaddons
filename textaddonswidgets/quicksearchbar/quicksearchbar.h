/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textaddonswidgets_export.h"
#include <QWidget>
class QLineEdit;
class QToolButton;
namespace TextAddonsWidgets
{
/*!
 * \class TextAddonsWidgets::QuickSearchBar
 * \inmodule TextAddonsWidgets
 * \inheaderfile TextAddonsWidgets/QuickSearchBar
 *
 * \brief The QuickSearchBar class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTADDONSWIDGETS_EXPORT QuickSearchBar : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Constructor for QuickSearchBar
     * \param parent The parent widget
     */
    explicit QuickSearchBar(QWidget *parent = nullptr);
    /*!
     * \brief Destructor for QuickSearchBar
     */
    ~QuickSearchBar() override;

    /*!
     * \brief Updates the visibility of next and previous buttons
     * \param next Whether the next button should be enabled
     * \param previous Whether the previous button should be enabled
     */
    void updateButtons(bool next, bool previous);
    /*!
     * \brief Returns the current search text
     * \return The search text
     */
    [[nodiscard]] QString searchText() const;
    /*!
     * \brief Sets the search text
     * \param str The text to set
     */
    void setTearchText(const QString &str);

    /*!
     * \brief Finds the next occurrence
     */
    void slotFindNext();
    /*!
     * \brief Finds the previous occurrence
     */
    void slotFindPrev();
    /*!
     * \brief Sets focus to the search line edit
     */
    void forceFocus();

Q_SIGNALS:
    /*!
     * \brief Emitted when search text is requested
     * \param txt The search text
     */
    void searchTextRequested(const QString &txt);
    /*!
     * \brief Emitted when find next is requested
     */
    void findNext();
    /*!
     * \brief Emitted when find previous is requested
     */
    void findPrev();

private:
    QLineEdit *const mSearchLineEdit;
    QToolButton *const mNextButton;
    QToolButton *const mPreviousButton;
};
}
