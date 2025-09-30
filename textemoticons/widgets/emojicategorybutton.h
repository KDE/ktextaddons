/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textemoticonswidgets_private_export.h"
#include <QToolButton>
namespace TextEmoticonsWidgets
{
class TEXTEMOTICONSWIDGETS_TESTS_EXPORT EmojiCategoryButton : public QToolButton
{
    Q_OBJECT
public:
    explicit EmojiCategoryButton(QWidget *parent = nullptr);
    ~EmojiCategoryButton() override;
};
}
