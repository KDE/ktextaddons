/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QListView>

namespace TextAutogenerateText
{
class TextAutoGenerateMessage;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutogenerateListView : public QListView
{
    Q_OBJECT
public:
    explicit TextAutogenerateListView(QWidget *parent = nullptr);
    ~TextAutogenerateListView() override;

    void setMessages(const QList<TextAutoGenerateMessage> &msg);

protected:
    void resizeEvent(QResizeEvent *ev) override;

    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT QStyleOptionViewItem listViewOptions() const;
    TEXTAUTOGENERATETEXT_NO_EXPORT void checkIfAtBottom();
    TEXTAUTOGENERATETEXT_NO_EXPORT void maybeScrollToBottom();
    TEXTAUTOGENERATETEXT_NO_EXPORT void updateVerticalPageStep();
    TEXTAUTOGENERATETEXT_NO_EXPORT void handleMouseEvent(QMouseEvent *event);
    virtual bool maybeStartDrag(QMouseEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index);
    virtual bool mouseEvent(QMouseEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index);

    bool mAtBottom = true;
    QPoint mPressedPosition;
    QPersistentModelIndex mCurrentIndex = {};
};
}
