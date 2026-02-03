/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollamacommon_export.h"
#include <QWidget>
namespace TextAutoGenerateText
{
class TextAutoGenerateModelAvailableListView;
class TextAutoGenerateModelSearchLineEdit;
}
class TEXTAUTOGENERATEOLLAMACOMMON_EXPORT OllamaCommonModelAvailableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaCommonModelAvailableWidget(QWidget *parent = nullptr);
    ~OllamaCommonModelAvailableWidget() override;

private:
    TextAutoGenerateText::TextAutoGenerateModelAvailableListView *const mAvailableListView;
    TextAutoGenerateText::TextAutoGenerateModelSearchLineEdit *const mSearchLineEdit;
};
