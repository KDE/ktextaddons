/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QTreeView>

namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TextAutoGenerateHistoryListHeadingsProxyModel;
class TextAutoGenerateHistorySortFilterProxyModel;
class TextAutoGenerateHistoryListViewDelegate;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateHistoryListView : public QTreeView
{
    Q_OBJECT
public:
    enum class Direction : uint8_t {
        Up,
        Down,
    };
    explicit TextAutoGenerateHistoryListView(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateHistoryListView() override;

    void slotSearchTextChanged(const QString &str);

    void selectNextChat(Direction direction = Direction::Down);

    [[nodiscard]] TextAutoGenerateHistorySortFilterProxyModel *filterModel() const;
Q_SIGNALS:
    void switchToChat(const QByteArray &uuid);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void addWaitingAnswerAnimation(const QModelIndex &index);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotClicked(const QModelIndex &idx);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotShowArchived();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotCurrentChatIdChanged();
    TEXTAUTOGENERATETEXT_NO_EXPORT void generalPaletteChanged();
    TextAutoGenerateHistorySortFilterProxyModel *const mHistoryProxyModel;
    TextAutoGenerateHistoryListHeadingsProxyModel *const mHistoryListHeadingsProxyModel;
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
    TextAutoGenerateHistoryListViewDelegate *const mDelegate;
    QColor mTextColor;
};
}
