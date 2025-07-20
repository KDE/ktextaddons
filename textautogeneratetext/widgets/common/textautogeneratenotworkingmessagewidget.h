/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <KMessageWidget>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateNotWorkingMessageWidget : public KMessageWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateNotWorkingMessageWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateNotWorkingMessageWidget() override;
Q_SIGNALS:
    void startOllama();
};
}
