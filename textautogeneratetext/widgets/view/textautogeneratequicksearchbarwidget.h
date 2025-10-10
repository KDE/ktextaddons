/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QWidget>
namespace TextAddonsWidgets
{
class SlideContainer;
}

namespace TextAutoGenerateText
{
class TextAutoGenerateQuickSearchBar;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateQuickSearchBarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateQuickSearchBarWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateQuickSearchBarWidget() override;

private:
    TextAddonsWidgets::SlideContainer *const mSliderContainer;
    TextAutoGenerateQuickSearchBar *const mQuickSearchBar;
};
}
