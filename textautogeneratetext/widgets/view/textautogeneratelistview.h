/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratebaselistview.h"
#include "textautogeneratetext_private_export.h"
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
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
    void leaveEvent(QEvent *event) override;
    [[nodiscard]] QString originalMessage(const QModelIndex &index) const override;

Q_SIGNALS:
    void editMessageRequested(const QModelIndex &index, const QList<QByteArray> &tools);
    void cancelRequested(const QByteArray &uuid);
    void refreshAnswerRequested(const QByteArray &chatId, const QModelIndex &indexAnswer, const QList<QByteArray> &tools);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void handleMouseEvent(QMouseEvent *event) override;
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotRemoveMessage(const QModelIndex &index);
    TEXTAUTOGENERATETEXT_NO_EXPORT void addSelectedMessageBackgroundAnimation(const QModelIndex &index);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotCancelRequested(const QModelIndex &index);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotEditMessage(const QModelIndex &index);
    TEXTAUTOGENERATETEXT_NO_EXPORT void addWaitingAnswerAnimation(const QModelIndex &index);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotRefreshRequested(const QModelIndex &index);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotCurrentChatIdChanged();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotUpdateView();
    TEXTAUTOGENERATETEXT_NO_EXPORT void goToMessageId(const QByteArray &uuid);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotRemoveRequested(const QModelIndex &index);
    TEXTAUTOGENERATETEXT_NO_EXPORT void clearEditingMode();
    QByteArray mMessageIdBeingEdited;
};
}
