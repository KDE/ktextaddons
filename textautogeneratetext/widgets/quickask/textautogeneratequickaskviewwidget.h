/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QWidget>
namespace TextAutoGenerateText
{
class TextAutoGenerateTextLineEditWidget;
class TextAutoGenerateResultWidget;
class TextAutoGenerateManager;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateQuickAskViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateQuickAskViewWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateQuickAskViewWidget() override;

private:
    TextAutoGenerateTextLineEditWidget *const mTextAutoGenerateTextLineWidget;
    TextAutoGenerateResultWidget *const mTextAutoGenerateResultWidget;
};
}
