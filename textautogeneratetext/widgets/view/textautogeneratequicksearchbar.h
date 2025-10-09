/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QWidget>
class QLineEdit;
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateQuickSearchBar : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateQuickSearchBar(QWidget *parent = nullptr);
    ~TextAutoGenerateQuickSearchBar() override;

Q_SIGNALS:
    void searchTextRequested(const QString &txt);

private:
    QLineEdit *const mSearchLineEdit;
};
}
