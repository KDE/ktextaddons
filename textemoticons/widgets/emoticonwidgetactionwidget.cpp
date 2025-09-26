/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "emoticonwidgetactionwidget.h"
#include "emoticonunicodeutils.h"
#include <QHBoxLayout>
#include <QIcon>
#include <QToolButton>

using namespace TextEmoticonsWidgets;
using namespace Qt::Literals::StringLiterals;
EmoticonWidgetActionWidget::EmoticonWidgetActionWidget(const QList<EmoticonWidgetAction::EmojiInfo> &emojis, QWidget *parent)
    : QWidget(parent)
    , mMainLayout(new QHBoxLayout(this))
{
    mMainLayout->setObjectName(u"mainLayout"_s);
    mMainLayout->setContentsMargins({});
    constexpr int defaultFontSize{14};
    QFont f;
    f.setPointSize(defaultFontSize);
    setFont(TextEmoticonsCore::EmoticonUnicodeUtils::emojiFontName());
    addDefaultEmojis(emojis);
}

EmoticonWidgetActionWidget::~EmoticonWidgetActionWidget() = default;

void EmoticonWidgetActionWidget::addDefaultEmojis(const QList<EmoticonWidgetAction::EmojiInfo> &emojis)
{
    for (const auto &emoji : emojis) {
        auto toolButton = new QToolButton(this);
        toolButton->setAutoRaise(true);
        toolButton->setText(emoji.emojiStr);
        mMainLayout->addWidget(toolButton);
        connect(toolButton, &QToolButton::clicked, this, [this, emoji]() {
            Q_EMIT insertEmoji(emoji.emojiStr);
            Q_EMIT insertEmojiIdentifier(emoji.emojiIdentifier);
        });
    }
    auto selectMoreEmojiButton = new QToolButton(this);
    selectMoreEmojiButton->setObjectName(u"selectMoreEmojiButton"_s);
    selectMoreEmojiButton->setIcon(QIcon::fromTheme(u"overflow-menu"_s));
    selectMoreEmojiButton->setAutoRaise(true);
    mMainLayout->addWidget(selectMoreEmojiButton);
    connect(selectMoreEmojiButton, &QToolButton::clicked, this, &EmoticonWidgetActionWidget::selectEmoji);

    mMainLayout->addStretch(1);
}
