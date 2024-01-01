/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textemoticonswidgets_private_export.h"
#include <QToolButton>
namespace TextEmoticonsWidgets
{
class TEXTEMOTICONSWIDGETS_TESTS_EXPORT EmoticonCategoryButton : public QToolButton
{
    Q_OBJECT
public:
    explicit EmoticonCategoryButton(QWidget *parent = nullptr);
    ~EmoticonCategoryButton() override;
};
}
