/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QWidget>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextConfigurePluginsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextConfigurePluginsWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateTextConfigurePluginsWidget() override;
};
}
