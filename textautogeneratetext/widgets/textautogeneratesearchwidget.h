/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QWidget>
namespace TextAutoGenerateText
{
class TextAutoGenerateSearchListView;
class TextAutoGenerateManager;
class TextAutoGenerateSearchLineEdit;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateSearchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSearchWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateSearchWidget() override;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotSearchTextChanged(const QString &str);
    TextAutoGenerateSearchListView *const mTextAutoGenerateSearchListView;
    TextAutoGenerateSearchLineEdit *const mSearchLineEdit;
};
}
