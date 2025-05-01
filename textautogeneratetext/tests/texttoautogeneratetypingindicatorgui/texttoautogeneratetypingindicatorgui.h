/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QPropertyAnimation>
#include <QWidget>

namespace TextAutogenerateText
{
class TextAutogenerateMessageWaitingAnswerAnimation;
}
class DotsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DotsWidget(QWidget *parent = nullptr);
    ~DotsWidget() override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    TextAutogenerateText::TextAutogenerateMessageWaitingAnswerAnimation *const mAnimation;
};
