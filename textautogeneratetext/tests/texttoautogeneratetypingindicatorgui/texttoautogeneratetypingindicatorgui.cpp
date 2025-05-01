/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttoautogeneratetypingindicatorgui.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QParallelAnimationGroup>
#include <QPauseAnimation>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QTimer>

Dot::Dot(QObject *parent, int duration, int index)
{
    auto scaleAnimation = new QPropertyAnimation(parent);

    scaleAnimation->setTargetObject(parent);
    scaleAnimation->setPropertyName("scale");
    scaleAnimation->setStartValue(1.0);
    scaleAnimation->setEndValue(1.33);
    scaleAnimation->setDuration(duration);

    auto opacityAnimation = new QPropertyAnimation(parent);
    opacityAnimation->setTargetObject(parent);
    opacityAnimation->setPropertyName("opacity");
    opacityAnimation->setStartValue(0.5);
    opacityAnimation->setEndValue(1.0);
    opacityAnimation->setDuration(duration);

    auto scaleAnimationDown = new QPropertyAnimation(parent);

    scaleAnimationDown->setTargetObject(parent);
    scaleAnimationDown->setPropertyName("scale");
    scaleAnimationDown->setStartValue(1.33);
    scaleAnimationDown->setEndValue(1.0);
    scaleAnimationDown->setDuration(duration);

    auto opacityAnimationDown = new QPropertyAnimation(parent);
    opacityAnimationDown->setTargetObject(parent);
    opacityAnimationDown->setPropertyName("opacity");
    opacityAnimationDown->setStartValue(1.0);
    opacityAnimationDown->setEndValue(0.5);
    opacityAnimationDown->setDuration(duration);

    auto groupUp = new QParallelAnimationGroup(parent);
    groupUp->addAnimation(scaleAnimation);
    groupUp->addAnimation(opacityAnimation);

    auto groupDown = new QParallelAnimationGroup(parent);
    groupDown->addAnimation(scaleAnimationDown);
    groupDown->addAnimation(opacityAnimationDown);

    auto sequencial = new QSequentialAnimationGroup(parent);
    const auto value = duration * index / 2;
    // qDebug() << " Pause value " << value;
    sequencial->addAnimation(groupUp);
    sequencial->addAnimation(groupDown);
    sequencial->setLoopCount(-1);
    QTimer::singleShot(value, parent, [sequencial]() {
        sequencial->start();
    });
}

DotWidget::DotWidget(int index, QWidget *parent)
    : QWidget(parent)
    , mScale(1.0)
    , mOpacity(0.5)
{
    int duration = 1000; // Duration in milliseconds
    new Dot(this, duration, index);
}

DotWidget::~DotWidget() = default;

qreal DotWidget::scale() const
{
    return mScale;
}

qreal DotWidget::opacity() const
{
    return mOpacity;
}

void DotWidget::setScale(qreal scale)
{
    if (mScale != scale) {
        mScale = scale;
        update();
    }
}

void DotWidget::setOpacity(qreal opacity)
{
    if (mOpacity != opacity) {
        mOpacity = opacity;
        update();
    }
}

void DotWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int dotSize = 20;
    int spacing = 40;

    painter.setOpacity(mOpacity);
    painter.save();
    painter.translate(spacing + (dotSize + spacing), height() / 2);
    painter.rotate(45);
    painter.scale(mScale, mScale);
    painter.setBrush(Qt::black);
    painter.drawEllipse(-dotSize / 2, -dotSize / 2, dotSize, dotSize);
    painter.restore();
}

DotsWidget::DotsWidget(QWidget *parent)
    : QWidget(parent)
{
    auto mainLayout = new QHBoxLayout(this);
    for (int i = 0; i < 3; ++i) {
        mainLayout->addWidget(new DotWidget(i, this));
    }
    setFixedSize(400, 400);
}

DotsWidget::~DotsWidget() = default;
