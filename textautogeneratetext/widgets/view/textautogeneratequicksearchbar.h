/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QWidget>
class QLineEdit;
class QToolButton;
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateQuickSearchBar : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateQuickSearchBar(QWidget *parent = nullptr);
    ~TextAutoGenerateQuickSearchBar() override;

    void updateButtons(bool next, bool previous);
    [[nodiscard]] QString searchText() const;
    void setTearchText(const QString &str);

Q_SIGNALS:
    void searchTextRequested(const QString &txt);

private:
    QLineEdit *const mSearchLineEdit;
    QToolButton *const mNextButton;
    QToolButton *const mPreviousButton;
};
}
