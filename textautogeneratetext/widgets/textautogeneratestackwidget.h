/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QWidget>
class QStackedWidget;
namespace TextAutogenerateText
{
class TextAutogenerateStackWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutogenerateStackWidget(QWidget *parent = nullptr);
    ~TextAutogenerateStackWidget() override;

private:
    QStackedWidget *const mStackedWidget;
};

}
