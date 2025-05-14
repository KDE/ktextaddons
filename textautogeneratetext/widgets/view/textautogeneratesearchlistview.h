/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QListView>
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TextAutoGenerateSearchListViewDelegate;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateSearchListView : public QListView
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSearchListView(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateSearchListView() override;

private:
    TextAutoGenerateText::TextAutoGenerateSearchListViewDelegate *const mDelegate;
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
};
}
