/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "emoticonwidgetaction.h"
#include "emoticonwidgetactionwidget.h"

using namespace TextEmoticonsWidgets;
using namespace Qt::Literals::StringLiterals;
EmoticonWidgetAction::EmoticonWidgetAction(QObject *parent)
    : QWidgetAction{parent}
    , mEmoticonWidgetActionWidget(new EmoticonWidgetActionWidget())
{
    mEmoticonWidgetActionWidget->setObjectName(u"mEmoticonWidgetActionWidget"_s);
    setDefaultWidget(mEmoticonWidgetActionWidget);
    connect(mEmoticonWidgetActionWidget, &EmoticonWidgetActionWidget::insertEmoji, this, &EmoticonWidgetAction::insertEmoji);
    connect(mEmoticonWidgetActionWidget, &EmoticonWidgetActionWidget::insertEmojiIdentifier, this, &EmoticonWidgetAction::insertEmojiIdentifier);
    connect(mEmoticonWidgetActionWidget, &EmoticonWidgetActionWidget::selectEmoji, this, &EmoticonWidgetAction::selectEmoji);
}

EmoticonWidgetAction::~EmoticonWidgetAction()
{
    delete mEmoticonWidgetActionWidget;
}

bool EmoticonWidgetAction::EmoticonInfo::isValid() const
{
    return !emojiIdentifier.isEmpty() && !emojiStr.isEmpty();
}

#include "moc_emoticonwidgetaction.cpp"
