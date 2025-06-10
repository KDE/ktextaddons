/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QWidget>
class QLineEdit;
namespace TextAutoGenerateText
{
class TextAutoGenerateTextInstancesManagerListView;
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextInstancesManagerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextInstancesManagerWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateTextInstancesManagerWidget() override;

private:
    TextAutoGenerateTextInstancesManagerListView *const mInstancesManagerListView;
    QLineEdit *const mSearchLineEdit;
};
}
