/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogeneratemessagewaitingansweranimationbase.h"
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateMessageWaitingAnswerAnimationBase::TextAutoGenerateMessageWaitingAnswerAnimationBase(QObject *parent)
    : QObject{parent}
{
    createAnimations();
}

TextAutoGenerateMessageWaitingAnswerAnimationBase::~TextAutoGenerateMessageWaitingAnswerAnimationBase() = default;

QPersistentModelIndex TextAutoGenerateMessageWaitingAnswerAnimationBase::modelIndex() const
{
    return mModelIndex;
}

void TextAutoGenerateMessageWaitingAnswerAnimationBase::setModelIndex(const QPersistentModelIndex &newModelIndex)
{
    mModelIndex = newModelIndex;
}

void TextAutoGenerateMessageWaitingAnswerAnimationBase::start()
{
    mSequencials->setLoopCount(-1);
    mSequencials->start();
}

void TextAutoGenerateMessageWaitingAnswerAnimationBase::stopAndDelete()
{
    mSequencials->stop();
    deleteLater();
}

int TextAutoGenerateMessageWaitingAnswerAnimationBase::count() const
{
    return mScaleOpacities.count();
}

void TextAutoGenerateMessageWaitingAnswerAnimationBase::createAnimations()
{
    mSequencials = new QSequentialAnimationGroup(this);
    const int duration = 300; // Ms
    mSequencials->addPause(duration);
    for (int i = 0; i < 3; i++) {
        mSequencials->addAnimation(createAnimation(i, duration));
    }
}

TextAutoGenerateMessageWaitingAnswerAnimationBase::ScaleAndOpacity TextAutoGenerateMessageWaitingAnswerAnimationBase::value(int i) const
{
    if (i >= 0 && i < mScaleOpacities.count()) {
        return mScaleOpacities.at(i);
    }
    return {};
}

QSequentialAnimationGroup *TextAutoGenerateMessageWaitingAnswerAnimationBase::createAnimation(int index, int duration)
{
    const ScaleAndOpacity s;
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

    auto sequential = new QSequentialAnimationGroup(this);
    const auto pauseValue = duration * (index + 1) / 2;
    sequential->addPause(pauseValue);
    sequential->addAnimation(groupUp);
    sequential->addAnimation(groupDown);
    sequential->setLoopCount(-1);
    sequential->start();
    return sequential;
}

QList<TextAutoGenerateMessageWaitingAnswerAnimationBase::ScaleAndOpacity> TextAutoGenerateMessageWaitingAnswerAnimationBase::scaleOpacities() const
{
    return mScaleOpacities;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateMessageWaitingAnswerAnimationBase::ScaleAndOpacity &t)
{
    d.space() << "scale:" << t.scale;
    d.space() << "opacity:" << t.opacity;
    return d;
}

#include "moc_textautogeneratemessagewaitingansweranimationbase.cpp"
