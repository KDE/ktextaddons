/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include <QListView>
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TextAutoGenerateListViewBaseDelegate;
class TextAutoGenerateBaseListView : public QListView
{
    Q_OBJECT
public:
    explicit TextAutoGenerateBaseListView(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateBaseListView() override;

    void slotSelectAll(const QModelIndex &index);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    [[nodiscard]] virtual QString originalMessage(const QModelIndex &index) const = 0;
    [[nodiscard]] QString selectedText(const QModelIndex &index) const;
    virtual void handleMouseEvent(QMouseEvent *event);

    void resizeEvent(QResizeEvent *ev) override;
    void slotCopyMessage(const QModelIndex &index);
    [[nodiscard]] QStyleOptionViewItem listViewOptions() const;
    void checkIfAtBottom();
    void maybeScrollToBottom();
    void updateVerticalPageStep();
    virtual bool maybeStartDrag(QMouseEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index);
    virtual bool mouseEvent(QMouseEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index);

    TextAutoGenerateListViewBaseDelegate *mDelegate = nullptr;
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
    QPoint mPressedPosition;
    QPersistentModelIndex mCurrentIndex = {};

private:
    bool mAtBottom = true;
};
}
