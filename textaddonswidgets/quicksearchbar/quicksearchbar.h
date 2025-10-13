/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textaddonswidgets_export.h"
#include <QWidget>
class QLineEdit;
class QToolButton;
namespace TextAddonsWidgets
{
class TEXTADDONSWIDGETS_EXPORT QuickSearchBar : public QWidget
{
    Q_OBJECT
public:
    explicit QuickSearchBar(QWidget *parent = nullptr);
    ~QuickSearchBar() override;

    void updateButtons(bool next, bool previous);
    [[nodiscard]] QString searchText() const;
    void setTearchText(const QString &str);

    void slotFindNext();
    void slotFindPrev();

Q_SIGNALS:
    void searchTextRequested(const QString &txt);
    void findNext();
    void findPrev();

private:
    QLineEdit *const mSearchLineEdit;
    QToolButton *const mNextButton;
    QToolButton *const mPreviousButton;
};
}
