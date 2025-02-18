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
    // TODO add emoji
    addItem(QStringLiteral("Original"), QVariant::fromValue(TextEmoticonsCore::EmojiModelManager::EmojiTone::Original));
    addItem(QStringLiteral("Light"), QVariant::fromValue(TextEmoticonsCore::EmojiModelManager::EmojiTone::Light));
    addItem(QStringLiteral("MediumLight"), QVariant::fromValue(TextEmoticonsCore::EmojiModelManager::EmojiTone::MediumLight));
    addItem(QStringLiteral("Medium"), QVariant::fromValue(TextEmoticonsCore::EmojiModelManager::EmojiTone::Medium));
    addItem(QStringLiteral("MediumDark"), QVariant::fromValue(TextEmoticonsCore::EmojiModelManager::EmojiTone::MediumDark));
    addItem(QStringLiteral("Dark"), QVariant::fromValue(TextEmoticonsCore::EmojiModelManager::EmojiTone::Dark));
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
