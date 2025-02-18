/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emoticontonecombobox.h"
#include "emoticonunicodeutils.h"

using namespace TextEmoticonsWidgets;
EmoticonToneComboBox::EmoticonToneComboBox(QWidget *parent)
    : QComboBox(parent)
{
    QFont f = font();
    f.setFamily(TextEmoticonsCore::EmoticonUnicodeUtils::emojiFontName());
    setFont(f);
    addItem(TextEmoticonsCore::EmoticonUnicodeUtils::escapeUnicodeEmoji(QStringLiteral("1f44d")),
            QVariant::fromValue(TextEmoticonsCore::EmojiModelManager::EmojiTone::Original));
    addItem(TextEmoticonsCore::EmoticonUnicodeUtils::escapeUnicodeEmoji(QStringLiteral("1f44d-1f3fb")),
            QVariant::fromValue(TextEmoticonsCore::EmojiModelManager::EmojiTone::Light));
    addItem(TextEmoticonsCore::EmoticonUnicodeUtils::escapeUnicodeEmoji(QStringLiteral("1f44d-1f3fc")),
            QVariant::fromValue(TextEmoticonsCore::EmojiModelManager::EmojiTone::MediumLight));
    addItem(TextEmoticonsCore::EmoticonUnicodeUtils::escapeUnicodeEmoji(QStringLiteral("1f44d-1f3fd")),
            QVariant::fromValue(TextEmoticonsCore::EmojiModelManager::EmojiTone::Medium));
    addItem(TextEmoticonsCore::EmoticonUnicodeUtils::escapeUnicodeEmoji(QStringLiteral("1f44d-1f3fe")),
            QVariant::fromValue(TextEmoticonsCore::EmojiModelManager::EmojiTone::MediumDark));
    addItem(TextEmoticonsCore::EmoticonUnicodeUtils::escapeUnicodeEmoji(QStringLiteral("1f44d-1f3ff")),
            QVariant::fromValue(TextEmoticonsCore::EmojiModelManager::EmojiTone::Dark));
}

EmoticonToneComboBox::~EmoticonToneComboBox() = default;

TextEmoticonsCore::EmojiModelManager::EmojiTone EmoticonToneComboBox::currentEmojiTone() const
{
    return currentData().value<TextEmoticonsCore::EmojiModelManager::EmojiTone>();
}

void EmoticonToneComboBox::setCurrentEmojiTone(TextEmoticonsCore::EmojiModelManager::EmojiTone tone)
{
    setCurrentIndex(findData(QVariant::fromValue(tone)));
}

#include "moc_emoticontonecombobox.cpp"
