/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QWidget>

#include "textautogeneratetext_export.h"
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextConfigurePromptWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextConfigurePromptWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateTextConfigurePromptWidget() override;
};

}
