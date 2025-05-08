/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogeneratemessagewaitingansweranimation.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratemessagesmodel.h"
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutogenerateMessageWaitingAnswerAnimation::TextAutogenerateMessageWaitingAnswerAnimation(QObject *parent)
    : QObject{parent}
{
    createAnimations();
    connect(TextAutoGenerateManager::self()->textAutoGenerateChatModel(),
            &QAbstractItemModel::dataChanged,
            this,
            [this](const QModelIndex &topLeft, const QModelIndex &, const QList<int> &roles) {
                if (roles.contains(TextAutoGenerateMessagesModel::FinishedRole)) {
                    if (roles.contains(TextAutoGenerateMessagesModel::FinishedRole)) {
                        const bool inProgress = !topLeft.data(TextAutoGenerateMessagesModel::FinishedRole).toBool();
                        if (!inProgress) {
                            if (mModelIndex == topLeft) {
                                Q_EMIT waitingAnswerDone(topLeft);
                                stopAndDelete();
                            }
                        }
                    }
                }
            });
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

void TextAutogenerateMessageWaitingAnswerAnimation::stopAndDelete()
{
    mSequencials->stop();
    deleteLater();
}

int TextAutogenerateMessageWaitingAnswerAnimation::count() const
{
    return mScaleOpacities.count();
}

void TextAutogenerateMessageWaitingAnswerAnimation::createAnimations()
{
    mSequencials = new QSequentialAnimationGroup(this);
    const int duration = 300; // Ms
    mSequencials->addPause(duration);
    for (int i = 0; i < 3; i++) {
        mSequencials->addAnimation(createAnimation(i, duration));
    }
}

TextAutogenerateMessageWaitingAnswerAnimation::ScaleAndOpacity TextAutogenerateMessageWaitingAnswerAnimation::value(int i) const
{
    if (i >= 0 && i < mScaleOpacities.count()) {
        return mScaleOpacities.at(i);
    }
    return {};
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
    const auto value = duration * (index + 1) / 2;
    sequencial->addPause(value);
    sequencial->addAnimation(groupUp);
    sequencial->addAnimation(groupDown);
    sequencial->setLoopCount(-1);
    sequencial->start();
    return sequencial;
}

QList<TextAutogenerateMessageWaitingAnswerAnimation::ScaleAndOpacity> TextAutogenerateMessageWaitingAnswerAnimation::scaleOpacities() const
{
    return mScaleOpacities;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutogenerateMessageWaitingAnswerAnimation::ScaleAndOpacity &t)
{
    d.space() << "scale:" << t.scale;
    d.space() << "opacity:" << t.opacity;
    return d;
}

#include "moc_textautogeneratemessagewaitingansweranimation.cpp"
