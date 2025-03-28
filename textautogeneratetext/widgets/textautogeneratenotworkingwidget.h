/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QWidget>

namespace TextAutogenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutogenerateNotWorkingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutogenerateNotWorkingWidget(QWidget *parent = nullptr);
    ~TextAutogenerateNotWorkingWidget() override;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotConfigure();
};
}
