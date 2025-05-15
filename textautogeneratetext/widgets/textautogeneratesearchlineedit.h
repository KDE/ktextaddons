/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_private_export.h"
#include <QLineEdit>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateSearchLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSearchLineEdit(QWidget *parent = nullptr);
    ~TextAutoGenerateSearchLineEdit() override;
};
}
