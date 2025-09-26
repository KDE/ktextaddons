/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "emoticonwidgetactionwidget.h"
#include "emoticonunicodeutils.h"
#include <QHBoxLayout>
#include <QIcon>
#include <QToolButton>
#include <TextEmoticonsCore/EmojiModelManager>
#include <TextEmoticonsCore/UnicodeEmoticonManager>

using namespace TextEmoticonsWidgets;
using namespace Qt::Literals::StringLiterals;
EmoticonWidgetActionWidget::EmoticonWidgetActionWidget(QWidget *parent)
    : QWidget(parent)
    , mMainLayout(new QHBoxLayout(this))
{
    mMainLayout->setObjectName(u"mainLayout"_s);
    mMainLayout->setContentsMargins({});
    constexpr int defaultFontSize{14};
    QFont f;
    f.setPointSize(defaultFontSize);
    setFont(TextEmoticonsCore::EmoticonUnicodeUtils::emojiFontName());
    addDefaultEmoticons(loadRecentsEmoticons());
}

EmoticonWidgetActionWidget::~EmoticonWidgetActionWidget() = default;

EmoticonWidgetAction::EmoticonInfo EmoticonWidgetActionWidget::generateEmoticonInfo(const QString &identifier) const
{
    const TextEmoticonsCore::UnicodeEmoticon unicode = TextEmoticonsCore::UnicodeEmoticonManager::self()->unicodeEmoticonForEmoji(identifier);
    const EmoticonWidgetAction::EmoticonInfo info = {.emojiStr = unicode.unicode(), .emojiIdentifier = unicode.identifier()};
    return info;
}

QList<EmoticonWidgetAction::EmoticonInfo> EmoticonWidgetActionWidget::loadRecentsEmoticons() const
{
    QList<EmoticonWidgetAction::EmoticonInfo> emoticons;
    const QStringList lst = TextEmoticonsCore::EmojiModelManager::self()->recentIdentifier();
    for (const QString &id : lst) {
        const EmoticonWidgetAction::EmoticonInfo info = generateEmoticonInfo(id);
        if (info.isValid()) {
            emoticons.append(info);
        }
        // Don't load all emoji history. Use the 5 first elements
        if (emoticons.count() == 5) {
            break;
        }
    }
    // qDebug() << "emoticons***** " << emoticons.count();
    // Make sure that we load 5 emoticons
    if (emoticons.count() < 5) {
        const QStringList defaultEmoticonList{
            u":thumbsup:"_s,
            u":thumbsdown:"_s,
            u":smiley:"_s,
            u":tada:"_s,
            u":eyes:"_s,
        };
        for (int i = emoticons.count(); i < 5; ++i) {
            emoticons.append(generateEmoticonInfo(defaultEmoticonList.at(i)));
        }
    }
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
