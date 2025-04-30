/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QPropertyAnimation>
#include <QWidget>

class Dot
{
public:
    Dot(QObject *parent, int duration, int index);
};

class DotWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal scale READ scale WRITE setScale)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

public:
    explicit DotWidget(int index, QWidget *parent = nullptr);
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

class DotsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DotsWidget(QWidget *parent = nullptr);
    ~DotsWidget() override;
};
