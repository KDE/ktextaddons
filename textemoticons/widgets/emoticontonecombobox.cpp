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
    addItem(QStringLiteral("Original"), QVariant::fromValue(TextEmoticonsCore::EmojiSortFilterProxyModel::EmojiTone::Original));
    addItem(QStringLiteral("Light"), QVariant::fromValue(TextEmoticonsCore::EmojiSortFilterProxyModel::EmojiTone::Light));
    addItem(QStringLiteral("MediumLight"), QVariant::fromValue(TextEmoticonsCore::EmojiSortFilterProxyModel::EmojiTone::MediumLight));
    addItem(QStringLiteral("Medium"), QVariant::fromValue(TextEmoticonsCore::EmojiSortFilterProxyModel::EmojiTone::Medium));
    addItem(QStringLiteral("MediumDark"), QVariant::fromValue(TextEmoticonsCore::EmojiSortFilterProxyModel::EmojiTone::MediumDark));
    addItem(QStringLiteral("Dark"), QVariant::fromValue(TextEmoticonsCore::EmojiSortFilterProxyModel::EmojiTone::Dark));
}

EmoticonToneComboBox::~EmoticonToneComboBox() = default;

TextEmoticonsCore::EmojiSortFilterProxyModel::EmojiTone EmoticonToneComboBox::currentEmojiTone() const
{
    return currentData().value<TextEmoticonsCore::EmojiSortFilterProxyModel::EmojiTone>();
}

#include "moc_emoticontonecombobox.cpp"
