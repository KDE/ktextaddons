/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QComboBox>

#include "textautogeneratetext_private_export.h"
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateSearchPromptComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSearchPromptComboBox(QWidget *parent = nullptr);
    ~TextAutoGenerateSearchPromptComboBox() override;
};
}
