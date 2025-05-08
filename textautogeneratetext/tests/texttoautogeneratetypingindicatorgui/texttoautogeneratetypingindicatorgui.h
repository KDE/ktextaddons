/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QWidget>

namespace TextAutoGenerateText
{
class TextAutoGenerateMessageWaitingAnswerAnimation;
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
    TextAutoGenerateText::TextAutoGenerateMessageWaitingAnswerAnimation *const mAnimation;
};
