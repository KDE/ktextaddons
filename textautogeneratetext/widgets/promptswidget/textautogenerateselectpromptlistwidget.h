/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_private_export.h"
#include <QListView>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateSelectPromptListWidget : public QListView
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSelectPromptListWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateSelectPromptListWidget() override;

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

Q_SIGNALS:
    void addPrompt();
    void removePrompt(const QByteArray &id);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotEditPrompt(const QModelIndex &index);
};
}
