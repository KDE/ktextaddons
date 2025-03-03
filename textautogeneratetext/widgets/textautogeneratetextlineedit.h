/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QLineEdit>
namespace TextAutogenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutogenerateTextLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit TextAutogenerateTextLineEdit(QWidget *parent = nullptr);
    ~TextAutogenerateTextLineEdit() override;
};
}
