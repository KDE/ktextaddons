/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QWidget>
namespace TextAutogenerateText
{
class TextAutogenerateListView;
class TextAutoGenerateMessage;
class TEXTAUTOGENERATETEXT_EXPORT TextAutogenerateResultWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutogenerateResultWidget(QWidget *parent = nullptr);
    ~TextAutogenerateResultWidget() override;

    void setMessages(const QList<TextAutoGenerateMessage> &msg);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void loadHistory();
    TEXTAUTOGENERATETEXT_NO_EXPORT void saveHistory();
    TextAutogenerateListView *const mTextAutogenerateListView;
};

}
