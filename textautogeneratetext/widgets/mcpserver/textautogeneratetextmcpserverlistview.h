/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QListView>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateTextMcpServerListView : public QListView
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextMcpServerListView(QWidget *parent = nullptr);
    ~TextAutoGenerateTextMcpServerListView() override;

    void slotSearchChanged(const QString &str);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotEditMcpServer(const QModelIndex &index);
};
}
