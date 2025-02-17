/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "emojisortfilterproxymodel.h"
#include "textemoticonswidgets_export.h"
#include <QComboBox>
namespace TextEmoticonsWidgets
{
class TEXTEMOTICONSWIDGETS_EXPORT EmoticonToneComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit EmoticonToneComboBox(QWidget *parent = nullptr);
    ~EmoticonToneComboBox() override;
    [[nodiscard]] TextEmoticonsCore::EmojiSortFilterProxyModel::EmojiTone currentEmojiTone() const;
};
}
