/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratelistviewbasedelegate.h"
#include "textautogeneratetext_private_export.h"
class QListView;
namespace TextAutoGenerateText
{
class TextAutoGenerateListViewTextSelection;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateSearchListViewDelegate : public TextAutoGenerateListViewBaseDelegate
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSearchListViewDelegate(QListView *view);
    ~TextAutoGenerateSearchListViewDelegate() override;

    [[nodiscard]] QTextDocument *documentForIndex(const QModelIndex &index, int width) const override;
};
}
