/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QWidget>

namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateQuickAskHeaderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateQuickAskHeaderWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateQuickAskHeaderWidget() override;

private:
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
};
}
