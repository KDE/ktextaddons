/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QWidget>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateShowModelInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateShowModelInfoWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateShowModelInfoWidget() override;
};
}
