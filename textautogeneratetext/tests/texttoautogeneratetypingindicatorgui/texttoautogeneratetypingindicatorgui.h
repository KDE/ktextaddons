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
    QPropertyAnimation scaleAnimation;
    QPropertyAnimation opacityAnimation;
    QSequentialAnimationGroup animationGroup;

    Dot(QObject *parent, int duration, int index);
};

class DotWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal scale READ scale WRITE setScale)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

public:
    DotWidget(QWidget *parent = nullptr);

    qreal scale() const
    {
        return m_scale;
    }

    qreal opacity() const
    {
        return m_opacity;
    }

public Q_SLOTS:
    void setScale(qreal scale)
    {
        if (m_scale != scale) {
            m_scale = scale;
            update();
        }
    }

    void setOpacity(qreal opacity)
    {
        if (m_opacity != opacity) {
            m_opacity = opacity;
            update();
        }
    }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    qreal m_scale;
    qreal m_opacity;
    QList<Dot *> dots;
};
