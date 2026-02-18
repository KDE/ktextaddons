/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textaddonswidgets_export.h"
#include <QWidget>

namespace TextAddonsWidgets
{
class SlideContainer;
class QuickSearchBar;
/*!
 * \class TextAddonsWidgets::QuickSearchBarWidget
 * \inmodule TextAddonsWidgets
 * \inheaderfile TextAddonsWidgets/QuickSearchBarWidget
 *
 * \brief The QuickSearchBarWidget class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTADDONSWIDGETS_EXPORT QuickSearchBarWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Constructor for QuickSearchBarWidget
     * \param parent The parent widget
     */
    explicit QuickSearchBarWidget(QWidget *parent = nullptr);
    /*!
     * \brief Destructor for QuickSearchBarWidget
     */
    ~QuickSearchBarWidget() override;

    /*!
     * \brief Slides the search bar in
     */
    void slideIn();
    /*!
     * \brief Slides the search bar out
     */
    void slideOut();
    /*!
     * \brief Updates the visibility of search navigation buttons
     * \param next Whether the next button should be enabled
     * \param previous Whether the previous button should be enabled
     */
    void updateButtons(bool next, bool previous);

Q_SIGNALS:
    /*!
     * \brief Emitted when search text is requested
     * \param txt The search text
     */
    void searchTextRequested(const QString &txt);
    /*!
     * \brief Emitted when close search bar is requested
     */
    void closeSearchBarRequested();
    /*!
     * \brief Emitted when find next is requested
     */
    void findNext();
    /*!
     * \brief Emitted when find previous is requested
     */
    void findPrev();

protected:
    /*!
     * \brief Handles events for the search bar widget
     * \param e The event that occurred
     * \return True if the event was handled, false otherwise
     */
    [[nodiscard]] bool event(QEvent *e) override;

private:
    TEXTADDONSWIDGETS_NO_EXPORT void closeBar();
    TextAddonsWidgets::SlideContainer *const mSliderContainer;
    QuickSearchBar *const mQuickSearchBar;
};
}
