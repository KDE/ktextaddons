/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogenerateselectedmessagebackgroundanimation.h"
#include "textautogeneratecolorsandmessageviewstyle.h"
#include <QPropertyAnimation>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutogenerateText;
TextAutogenerateSelectedMessageBackgroundAnimation::TextAutogenerateSelectedMessageBackgroundAnimation(QObject *parent)
    : QObject{parent}
{
}

TextAutogenerateSelectedMessageBackgroundAnimation::~TextAutogenerateSelectedMessageBackgroundAnimation() = default;

QColor TextAutogenerateSelectedMessageBackgroundAnimation::backgroundColor() const
{
    return m_backgroundColor;
}

QPersistentModelIndex TextAutogenerateSelectedMessageBackgroundAnimation::modelIndex() const
{
    return mModelIndex;
}

void TextAutogenerateSelectedMessageBackgroundAnimation::setModelIndex(const QPersistentModelIndex &newModelIndex)
{
    mModelIndex = newModelIndex;
}

void TextAutogenerateSelectedMessageBackgroundAnimation::setBackgroundColor(const QColor &newBackgroundColor)
{
    if (m_backgroundColor == newBackgroundColor)
        return;
    m_backgroundColor = newBackgroundColor;
    Q_EMIT backgroundColorChanged();
}

void TextAutogenerateSelectedMessageBackgroundAnimation::start()
{
    auto animation = new QPropertyAnimation(this, "backgroundColor"_ba, this);
    animation->setDuration(2000);
    const auto color = TextAutogenerateColorsAndMessageViewStyle::self().schemeView().foreground(KColorScheme::NeutralText).color();
    animation->setStartValue(color);
    animation->setEndValue(QColor(Qt::transparent));
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->start();
    connect(animation, &QPropertyAnimation::finished, this, [this]() {
        Q_EMIT animationFinished();
        deleteLater();
    });
}

#include "moc_textautogenerateselectedmessagebackgroundanimation.cpp"
