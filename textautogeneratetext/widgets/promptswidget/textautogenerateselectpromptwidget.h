/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_private_export.h"
#include <QWidget>
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TextAutoGenerateTextPromptModel;
class TextAutoGenerateSelectPromptListWidget;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateSelectPromptWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSelectPromptWidget(TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateSelectPromptWidget() override;

private:
    TextAutoGenerateSelectPromptListWidget *const mListWidget;
    TextAutoGenerateTextPromptModel *const mPromptModel;
};
}
