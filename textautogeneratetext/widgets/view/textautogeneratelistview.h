/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratebaselistview.h"
#include "textautogeneratetext_private_export.h"
#include <QListView>
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TextAutoGenerateMessage;
class TextAutoGenerateListViewDelegate;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateListView : public TextAutoGenerateBaseListView
{
    Q_OBJECT
public:
    explicit TextAutoGenerateListView(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateListView() override;

    void handleKeyPressEvent(QKeyEvent *ev);

    void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible) override;

    void editingFinished(const QByteArray &uuid);

    void setModel(QAbstractItemModel *newModel) override;

protected:
    void resizeEvent(QResizeEvent *ev) override;

    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;
    void leaveEvent(QEvent *event) override;

Q_SIGNALS:
    void editMessageRequested(const QModelIndex &index);
    void cancelRequested(const QByteArray &uuid);
    void refreshAnswerRequested(const QByteArray &chatId, const QModelIndex &index);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void handleMouseEvent(QMouseEvent *event);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotSelectAll(const QModelIndex &index);
    TEXTAUTOGENERATETEXT_NO_EXPORT virtual bool maybeStartDrag(QMouseEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index);
    TEXTAUTOGENERATETEXT_NO_EXPORT virtual bool mouseEvent(QMouseEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotRemoveMessage(const QModelIndex &index);
    TEXTAUTOGENERATETEXT_NO_EXPORT void addSelectedMessageBackgroundAnimation(const QModelIndex &index);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotCancelRequested(const QModelIndex &index);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotEditMessage(const QModelIndex &index);
    TEXTAUTOGENERATETEXT_NO_EXPORT void addWaitingAnswerAnimation(const QModelIndex &index);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotRefreshRequested(const QModelIndex &index);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotCurrentChatIdChanged();

    QPersistentModelIndex mCurrentIndex = {};
    TextAutoGenerateListViewDelegate *const mDelegate;
};
}
