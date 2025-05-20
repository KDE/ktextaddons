/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratebaselistview.h"
#include "textautogeneratetext_private_export.h"
#include <TextAutoGenerateText/TextAutoGenerateSearchMessage>
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TextAutoGenerateSearchMessagesModel;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateSearchListView : public TextAutoGenerateBaseListView
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSearchListView(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateSearchListView() override;

    void setSearchMessages(const QList<TextAutoGenerateSearchMessage> &msgs);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotGoToMessage(const QUrl &link);
    TextAutoGenerateSearchMessagesModel *const mModel;
};
}
