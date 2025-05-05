/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QTreeView>

namespace TextAutogenerateText
{
class TextAutoGenerateHistoryListHeadingsProxyModel;
class TextAutoGenerateHistorySortFilterProxyModel;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutogenerateHistoryListView : public QTreeView
{
    Q_OBJECT
public:
    explicit TextAutogenerateHistoryListView(QWidget *parent = nullptr);
    ~TextAutogenerateHistoryListView() override;

    void slotSearchTextChanged(const QString &str);

Q_SIGNALS:
    void goToDiscussion(const QByteArray &uuid);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotClicked(const QModelIndex &idx);
    TextAutoGenerateHistorySortFilterProxyModel *const mHistoryProxyModel;
    TextAutoGenerateHistoryListHeadingsProxyModel *const mHistoryListHeadingsProxyModel;
};
}
