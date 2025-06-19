/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QComboBox>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextModelComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextModelComboBox(QWidget *parent = nullptr);
    ~TextAutoGenerateTextModelComboBox() override;
};
}
