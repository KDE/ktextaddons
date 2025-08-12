/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogenerateselectedmessagebackgroundanimation.h"
#include "textautogeneratecolorsandmessageviewstyle.h"
#include <QPropertyAnimation>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;

TextAutoGenerateSelectedMessageBackgroundAnimation::TextAutoGenerateSelectedMessageBackgroundAnimation(QObject *parent)
    : QObject{parent}
{
}

TextAutoGenerateSelectedMessageBackgroundAnimation::~TextAutoGenerateSelectedMessageBackgroundAnimation() = default;

QColor TextAutoGenerateSelectedMessageBackgroundAnimation::backgroundColor() const
{
    return m_backgroundColor;
}

QPersistentModelIndex TextAutoGenerateSelectedMessageBackgroundAnimation::modelIndex() const
{
    return mModelIndex;
}

void TextAutoGenerateSelectedMessageBackgroundAnimation::setModelIndex(const QPersistentModelIndex &newModelIndex)
{
    mModelIndex = newModelIndex;
}

void TextAutoGenerateSelectedMessageBackgroundAnimation::setBackgroundColor(const QColor &newBackgroundColor)
{
    if (m_backgroundColor == newBackgroundColor) {
        return;
    }
    m_backgroundColor = newBackgroundColor;
    Q_EMIT backgroundColorChanged();
}

void TextAutoGenerateSelectedMessageBackgroundAnimation::start()
{
    auto animation = new QPropertyAnimation(this, "backgroundColor"_ba, this);
    animation->setDuration(2000);
    const auto color = TextAutoGenerateColorsAndMessageViewStyle::self().schemeView().foreground(KColorScheme::NeutralText).color();
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
