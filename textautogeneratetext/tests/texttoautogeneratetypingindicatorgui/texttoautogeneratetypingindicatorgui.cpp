/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttoautogeneratetypingindicatorgui.h"
#include <QPainter>
#include <QParallelAnimationGroup>
#include <QPauseAnimation>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QTimer>

Dot::Dot(QObject *parent, int duration, int index)
{
    scaleAnimation.setTargetObject(parent);
    scaleAnimation.setPropertyName("scale");
    scaleAnimation.setStartValue(1.0);
    scaleAnimation.setEndValue(1.33);
    scaleAnimation.setDuration(duration);

    opacityAnimation.setTargetObject(parent);
    opacityAnimation.setPropertyName("opacity");
    opacityAnimation.setStartValue(0.5);
    opacityAnimation.setEndValue(1.0);
    opacityAnimation.setDuration(duration);

    QParallelAnimationGroup *group = new QParallelAnimationGroup(parent);
    group->addAnimation(&scaleAnimation);
    group->addAnimation(&opacityAnimation);

    QSequentialAnimationGroup *sequencial = new QSequentialAnimationGroup(parent);
    sequencial->addAnimation(group);
    sequencial->addPause(static_cast<int>((double)duration / (double)(index + 1)));
    sequencial->setLoopCount(-1);
    sequencial->start();
}

DotWidget::DotWidget(QWidget *parent)
    : QWidget(parent)
    , m_scale(1.0)
    , m_opacity(0.5)
{
    setFixedSize(200, 200);
    int duration = 1000; // Duration in milliseconds
    for (int i = 0; i < 3; ++i) {
        dots.append(new Dot(this, duration, i));
    }
}

void DotWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int dotSize = 20;
    int spacing = 40;

    for (int i = 0; i < 3; ++i) {
        painter.setOpacity(m_opacity);
        painter.save();
        painter.translate(spacing + i * (dotSize + spacing), height() / 2);
        painter.rotate(45);
        painter.scale(m_scale, m_scale);
        painter.setBrush(Qt::black);
        painter.drawEllipse(-dotSize / 2, -dotSize / 2, dotSize, dotSize);
        painter.restore();
    }
}
