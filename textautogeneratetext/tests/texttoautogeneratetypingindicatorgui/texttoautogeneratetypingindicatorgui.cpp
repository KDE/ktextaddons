/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttoautogeneratetypingindicatorgui.h"
#include <widgets/view/textautogeneratemessagewaitingansweranimation.h>

#include <QPainter>

DotsWidget::DotsWidget(QWidget *parent)
    : QWidget(parent)
    , mAnimation(new TextAutogenerateText::TextAutogenerateMessageWaitingAnswerAnimation(this))
{
    setFixedSize(400, 400);
    mAnimation->start();
    connect(mAnimation, &TextAutogenerateText::TextAutogenerateMessageWaitingAnswerAnimation::valueChanged, this, [this]() {
        update();
    });
}

DotsWidget::~DotsWidget() = default;

void DotsWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int dotSize = 20;
    int spacing = 40;

    for (int i = 0; i < mAnimation->count(); ++i) {
        const TextAutogenerateText::TextAutogenerateMessageWaitingAnswerAnimation::ScaleAndOpacity value = mAnimation->value(i);
        painter.setOpacity(value.opacity);
        painter.save();
        painter.translate(spacing + i * (dotSize + spacing), height() / 2);
        painter.rotate(45);
        painter.scale(value.scale, value.scale);
        painter.setBrush(Qt::black);
        painter.drawEllipse(-dotSize / 2, -dotSize / 2, dotSize, dotSize);
        painter.restore();
    }
}

#include "moc_texttoautogeneratetypingindicatorgui.cpp"
