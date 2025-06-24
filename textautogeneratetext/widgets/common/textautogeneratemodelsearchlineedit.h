/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QLineEdit>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateModelSearchLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit TextAutoGenerateModelSearchLineEdit(QWidget *parent = nullptr);
    ~TextAutoGenerateModelSearchLineEdit() override;
};
}
