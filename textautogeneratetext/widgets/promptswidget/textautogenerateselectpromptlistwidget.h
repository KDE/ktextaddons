/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_private_export.h"
#include <QListWidget>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateSelectPromptListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSelectPromptListWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateSelectPromptListWidget() override;
};
}
