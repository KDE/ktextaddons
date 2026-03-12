/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QListView>
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TextAutoGenerateTextMcpServerSortFilterProxyModel;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateTextMcpServerListView : public QListView
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextMcpServerListView(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateTextMcpServerListView() override;

    void slotSearchChanged(const QString &str);

Q_SIGNALS:
    void addServer();
    void editServer(const QByteArray &id);
    void removeServer(const QByteArray &id);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotEditMcpServer(const QModelIndex &index);
    TextAutoGenerateTextMcpServerSortFilterProxyModel *const mSortFilterProxyModel;
};
}
