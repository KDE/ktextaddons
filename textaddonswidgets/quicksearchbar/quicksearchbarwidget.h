/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textaddonswidgets_export.h"
#include <QWidget>

namespace TextAddonsWidgets
{
class SlideContainer;
class QuickSearchBar;
class TEXTADDONSWIDGETS_EXPORT QuickSearchBarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QuickSearchBarWidget(QWidget *parent = nullptr);
    ~QuickSearchBarWidget() override;

    void slideIn();
    void slideOut();

Q_SIGNALS:
    void searchTextRequested(const QString &txt);
    void closeSearchBarRequested();
    void findNext();
    void findPrev();

protected:
    [[nodiscard]] bool event(QEvent *e) override;

private:
    TEXTADDONSWIDGETS_NO_EXPORT void closeBar();
    TextAddonsWidgets::SlideContainer *const mSliderContainer;
    QuickSearchBar *const mQuickSearchBar;
};
}
