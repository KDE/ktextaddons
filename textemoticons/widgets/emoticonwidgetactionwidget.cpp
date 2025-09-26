/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "emoticonwidgetactionwidget.h"
#include "emoticonunicodeutils.h"
#include <QHBoxLayout>
#include <QIcon>
#include <QToolButton>
#include <TextEmoticonsCore/UnicodeEmoticonManager>

using namespace TextEmoticonsWidgets;
using namespace Qt::Literals::StringLiterals;
EmoticonWidgetActionWidget::EmoticonWidgetActionWidget(const QList<EmoticonWidgetAction::EmoticonInfo> &emoticons, QWidget *parent)
    : QWidget(parent)
    , mMainLayout(new QHBoxLayout(this))
{
    mMainLayout->setObjectName(u"mainLayout"_s);
    mMainLayout->setContentsMargins({});
    constexpr int defaultFontSize{14};
    QFont f;
    f.setPointSize(defaultFontSize);
    setFont(TextEmoticonsCore::EmoticonUnicodeUtils::emojiFontName());
    addDefaultEmoticons(emoticons.isEmpty() ? defaultEmoticons() : emoticons);
}

EmoticonWidgetActionWidget::~EmoticonWidgetActionWidget() = default;

QList<EmoticonWidgetAction::EmoticonInfo> EmoticonWidgetActionWidget::defaultEmoticons() const
{
    TextEmoticonsCore::UnicodeEmoticon unicode = TextEmoticonsCore::UnicodeEmoticonManager::self()->unicodeEmoticonForEmoji(u":thumbsup:"_s);
    const QList<EmoticonWidgetAction::EmoticonInfo> emoticons = {
        {.emojiStr = unicode.unicode(), .emojiIdentifier = u":thumbsup:"_s},
        {.emojiStr = u"👎"_s, .emojiIdentifier = u":thumbsdown:"_s},
        {.emojiStr = u"😄"_s, .emojiIdentifier = u":smiley:"_s},
        {.emojiStr = u"🎉"_s, .emojiIdentifier = u":tada:"_s},
        {.emojiStr = u"👀"_s, .emojiIdentifier = u":eyes:"_s},
    };
    return emoticons;
}

void EmoticonWidgetActionWidget::addDefaultEmoticons(const QList<EmoticonWidgetAction::EmoticonInfo> &emoticons)
{
    for (const auto &emoticon : emoticons) {
        auto toolButton = new QToolButton(this);
        toolButton->setAutoRaise(true);
        toolButton->setText(emoticon.emojiStr);
        mMainLayout->addWidget(toolButton);
        connect(toolButton, &QToolButton::clicked, this, [this, emoticon]() {
            Q_EMIT insertEmoji(emoticon.emojiStr);
            Q_EMIT insertEmojiIdentifier(emoticon.emojiIdentifier);
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

#include "moc_emoticonwidgetactionwidget.cpp"
