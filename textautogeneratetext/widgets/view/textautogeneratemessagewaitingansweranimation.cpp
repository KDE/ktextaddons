/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogeneratemessagewaitingansweranimation.h"

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
    // TODO
}

TextAutogenerateMessageWaitingAnswerAnimation::ScaleAndOpacity TextAutogenerateMessageWaitingAnswerAnimation::value(int i) const
{
    if (i >= 0 && i < mScaleOpacities.count()) {
        return {};
    }
    return mScaleOpacities.at(i);
}

#include "moc_textautogeneratemessagewaitingansweranimation.cpp"
