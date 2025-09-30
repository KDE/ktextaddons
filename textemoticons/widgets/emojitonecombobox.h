/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textemoticonswidgets_private_export.h"
#include <QComboBox>
#include <TextEmoticonsCore/EmojiModelManager>
namespace TextEmoticonsWidgets
{
class TEXTEMOTICONSWIDGETS_TESTS_EXPORT EmojiToneComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit EmojiToneComboBox(QWidget *parent = nullptr);
    ~EmojiToneComboBox() override;
    [[nodiscard]] TextEmoticonsCore::EmojiModelManager::EmojiTone currentEmojiTone() const;
    void setCurrentEmojiTone(TextEmoticonsCore::EmojiModelManager::EmojiTone tone);
};
}
