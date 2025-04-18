/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QWidget>
class QLineEdit;
namespace TextAutogenerateText
{
class TextAutogenerateHistoryListView;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutogenerateHistoryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutogenerateHistoryWidget(QWidget *parent = nullptr);
    ~TextAutogenerateHistoryWidget() override;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void saveHistory();
    TEXTAUTOGENERATETEXT_NO_EXPORT void loadHistory();
    TextAutogenerateHistoryListView *const mTextAutogenerateHistoryListView;
    QLineEdit *const mSearchLineEdit;
};
}
