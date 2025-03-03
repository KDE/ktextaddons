/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_private_export.h"
#include <QWidget>
namespace TextAutogenerateText
{
class TextAutogenerateResultWidget;
class TextAutogenerateTextLineEdit;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutogenerateTextLineEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutogenerateTextLineEditWidget(QWidget *parent = nullptr);
    ~TextAutogenerateTextLineEditWidget() override;

private:
    TextAutogenerateResultWidget *const mTextAutogenerateResultWidget;
    TextAutogenerateTextLineEdit *const mTextAutogenerateTextLineEdit;
};
}
