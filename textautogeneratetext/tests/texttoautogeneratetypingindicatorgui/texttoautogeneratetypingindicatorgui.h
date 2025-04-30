/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QWidget>
/*
class TextAutoGenerateWidgetGui : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateWidgetGui(QWidget *parent = nullptr);
    ~TextAutoGenerateWidgetGui() override;
};
*/
#include <QPainter>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QTimer>
#include <QWidget>

class Dot
{
public:
    Dot(QObject *parent, int duration, int index);

private:
    QPropertyAnimation scaleAnimation;
    QPropertyAnimation opacityAnimation;
    QSequentialAnimationGroup animationGroup;
};

class DotWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal scale READ scale WRITE setScale)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

public:
    explicit DotWidget(QWidget *parent = nullptr);
    ~DotWidget() override;

    [[nodiscard]] qreal scale() const;

    [[nodiscard]] qreal opacity() const;

public Q_SLOTS:
    void setScale(qreal scale);

    void setOpacity(qreal opacity);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    qreal mScale = 0.0;
    qreal mOpacity = 0.0;
    QList<Dot *> mDots;
};
