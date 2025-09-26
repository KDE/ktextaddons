/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "emoticonwidgetaction.h"
#include "emoticonwidgetactionwidget.h"

using namespace TextEmoticonsWidgets;
using namespace Qt::Literals::StringLiterals;
EmoticonWidgetAction::EmoticonWidgetAction(const QList<EmoticonWidgetAction::EmojiInfo> &emojis, QObject *parent)
    : QWidgetAction{parent}
    , mEmoticonWidgetActionWidget(new EmoticonWidgetActionWidget(emojis))
{
    setDefaultWidget(mEmoticonWidgetActionWidget);
    connect(mEmoticonWidgetActionWidget, &EmoticonWidgetActionWidget::insertEmoji, this, &EmoticonWidgetAction::insertEmoji);
    connect(mEmoticonWidgetActionWidget, &EmoticonWidgetActionWidget::insertEmojiIdentifier, this, &EmoticonWidgetAction::insertEmojiIdentifier);
    connect(mEmoticonWidgetActionWidget, &EmoticonWidgetActionWidget::selectEmoji, this, &EmoticonWidgetAction::selectEmoji);
}

EmoticonWidgetAction::~EmoticonWidgetAction()
{
    delete mEmoticonWidgetActionWidget;
}

#include "moc_emoticonwidgetaction.cpp"
