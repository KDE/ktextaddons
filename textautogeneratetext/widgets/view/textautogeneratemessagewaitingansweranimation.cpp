/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogeneratemessagewaitingansweranimation.h"

#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutogenerateText;
TextAutogenerateMessageWaitingAnswerAnimation::TextAutogenerateMessageWaitingAnswerAnimation(QObject *parent)
    : QObject{parent}
{
}

TextAutogenerateMessageWaitingAnswerAnimation::~TextAutogenerateMessageWaitingAnswerAnimation() = default;

QPersistentModelIndex TextAutogenerateMessageWaitingAnswerAnimation::modelIndex() const
{
    return mModelIndex;
}

void TextAutogenerateMessageWaitingAnswerAnimation::setModelIndex(const QPersistentModelIndex &newModelIndex)
{
    mModelIndex = newModelIndex;
}

void TextAutogenerateMessageWaitingAnswerAnimation::start()
{
    mSequencials->setLoopCount(-1);
    mSequencials->start();
}

void TextAutogenerateMessageWaitingAnswerAnimation::createAnimations()
{
    mSequencials = new QSequentialAnimationGroup(this);
    const int duration = 2000; // Ms
    for (int i = 0; i < 3; i++) {
        mSequencials->addAnimation(createAnimation(i, duration));
    }
}

TextAutogenerateMessageWaitingAnswerAnimation::ScaleAndOpacity TextAutogenerateMessageWaitingAnswerAnimation::value(int i) const
{
    if (i >= 0 && i < mScaleOpacities.count()) {
        return {};
    }
    return mScaleOpacities.at(i);
}

QSequentialAnimationGroup *TextAutogenerateMessageWaitingAnswerAnimation::createAnimation(int index, int duration)
{
    ScaleAndOpacity s;
    mScaleOpacities.append(s);
    auto scaleAnimationUp = new QPropertyAnimation(this);

    scaleAnimationUp->setTargetObject(this);
    scaleAnimationUp->setStartValue(1.0);
    scaleAnimationUp->setEndValue(1.33);
    scaleAnimationUp->setDuration(duration);
    connect(scaleAnimationUp, &QPropertyAnimation::valueChanged, this, [this, index](const QVariant &value) {
        ScaleAndOpacity &s = mScaleOpacities[index];
        s.scale = value.toDouble();
        Q_EMIT valueChanged();
    });

    auto opacityAnimationUp = new QPropertyAnimation(this);
    opacityAnimationUp->setTargetObject(this);
    opacityAnimationUp->setStartValue(0.5);
    opacityAnimationUp->setEndValue(1.0);
    opacityAnimationUp->setDuration(duration);
    connect(opacityAnimationUp, &QPropertyAnimation::valueChanged, this, [this, index](const QVariant &value) {
        ScaleAndOpacity &s = mScaleOpacities[index];
        s.opacity = value.toDouble();
        Q_EMIT valueChanged();
    });

    auto scaleAnimationDown = new QPropertyAnimation(this);

    scaleAnimationDown->setTargetObject(this);
    scaleAnimationDown->setStartValue(1.33);
    scaleAnimationDown->setEndValue(1.0);
    scaleAnimationDown->setDuration(duration);
    connect(scaleAnimationDown, &QPropertyAnimation::valueChanged, this, [this, index](const QVariant &value) {
        ScaleAndOpacity &s = mScaleOpacities[index];
        s.scale = value.toDouble();
        Q_EMIT valueChanged();
    });

    auto opacityAnimationDown = new QPropertyAnimation(this);
    opacityAnimationDown->setTargetObject(this);
    opacityAnimationDown->setStartValue(1.0);
    opacityAnimationDown->setEndValue(0.5);
    opacityAnimationDown->setDuration(duration);
    connect(opacityAnimationDown, &QPropertyAnimation::valueChanged, this, [this, index](const QVariant &value) {
        ScaleAndOpacity &s = mScaleOpacities[index];
        s.opacity = value.toDouble();
        Q_EMIT valueChanged();
    });

    auto groupUp = new QParallelAnimationGroup(this);
    groupUp->addAnimation(scaleAnimationUp);
    groupUp->addAnimation(opacityAnimationUp);

    auto groupDown = new QParallelAnimationGroup(this);
    groupDown->addAnimation(scaleAnimationDown);
    groupDown->addAnimation(opacityAnimationDown);

    auto sequencial = new QSequentialAnimationGroup(this);
    const auto value = duration * index / 2;
    // qDebug() << " Pause value " << value;
    // TODO add pause
    sequencial->addAnimation(groupUp);
    sequencial->addAnimation(groupDown);
    sequencial->setLoopCount(-1);
    return sequencial;
}

#include "moc_textautogeneratemessagewaitingansweranimation.cpp"
