/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emojitonecombobox.h"

#include "emoticonunicodeutils.h"
#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;
using namespace TextEmoticonsWidgets;
EmojiToneComboBox::EmojiToneComboBox(QWidget *parent)
    : QComboBox(parent)
{
    setToolTip(i18n("Select Tone"));
    QFont f = font();
    f.setFamily(TextEmoticonsCore::EmoticonUnicodeUtils::emojiFontName());
    setFont(f);
    addItem(TextEmoticonsCore::EmoticonUnicodeUtils::escapeUnicodeEmoji(u"1f44d"_s),
            QVariant::fromValue(TextEmoticonsCore::EmojiModelManager::EmojiTone::Original));
    addItem(TextEmoticonsCore::EmoticonUnicodeUtils::escapeUnicodeEmoji(u"1f44d-1f3fb"_s),
            QVariant::fromValue(TextEmoticonsCore::EmojiModelManager::EmojiTone::Light));
    addItem(TextEmoticonsCore::EmoticonUnicodeUtils::escapeUnicodeEmoji(u"1f44d-1f3fc"_s),
            QVariant::fromValue(TextEmoticonsCore::EmojiModelManager::EmojiTone::MediumLight));
    addItem(TextEmoticonsCore::EmoticonUnicodeUtils::escapeUnicodeEmoji(u"1f44d-1f3fd"_s),
            QVariant::fromValue(TextEmoticonsCore::EmojiModelManager::EmojiTone::Medium));
    addItem(TextEmoticonsCore::EmoticonUnicodeUtils::escapeUnicodeEmoji(u"1f44d-1f3fe"_s),
            QVariant::fromValue(TextEmoticonsCore::EmojiModelManager::EmojiTone::MediumDark));
    addItem(TextEmoticonsCore::EmoticonUnicodeUtils::escapeUnicodeEmoji(u"1f44d-1f3ff"_s),
            QVariant::fromValue(TextEmoticonsCore::EmojiModelManager::EmojiTone::Dark));
}

EmojiToneComboBox::~EmojiToneComboBox() = default;

TextEmoticonsCore::EmojiModelManager::EmojiTone EmojiToneComboBox::currentEmojiTone() const
{
    return currentData().value<TextEmoticonsCore::EmojiModelManager::EmojiTone>();
}

void EmojiToneComboBox::setCurrentEmojiTone(TextEmoticonsCore::EmojiModelManager::EmojiTone tone)
{
    setCurrentIndex(findData(QVariant::fromValue(tone)));
}

#include "moc_emojitonecombobox.cpp"
