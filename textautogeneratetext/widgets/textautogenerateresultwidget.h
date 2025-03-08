/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QWidget>
namespace TextAutogenerateText
{
class TextAutogenerateListView;
class TEXTAUTOGENERATETEXT_EXPORT TextAutogenerateResultWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutogenerateResultWidget(QWidget *parent = nullptr);
    ~TextAutogenerateResultWidget() override;

private:
    TextAutogenerateListView *const mTextAutogenerateListView;
};

}
