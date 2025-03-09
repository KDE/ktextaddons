/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QListView>

namespace TextAutogenerateText
{
class TextAutoGenerateChatModel;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutogenerateListView : public QListView
{
    Q_OBJECT
public:
    explicit TextAutogenerateListView(QWidget *parent = nullptr);
    ~TextAutogenerateListView() override;

private:
    TextAutoGenerateChatModel *const mTextAutoGenerateChatModel;
};
}
