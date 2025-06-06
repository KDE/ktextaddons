/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QWidget>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateTextInstanceManagerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextInstanceManagerWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateTextInstanceManagerWidget() override;
};
}
