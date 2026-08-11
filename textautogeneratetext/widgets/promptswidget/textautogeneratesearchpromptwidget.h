/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QWidget>

#include "textautogeneratetext_private_export.h"
class QLineEdit;
namespace TextAutoGenerateText
{
class TextAutoGenerateSearchPromptComboBox;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateSearchPromptWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSearchPromptWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateSearchPromptWidget() override;

private:
    QLineEdit *const mSearchLineEdit;
    TextAutoGenerateSearchPromptComboBox *const mPromptComboBox;
};
}
