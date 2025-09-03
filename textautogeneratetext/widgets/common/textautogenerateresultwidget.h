/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QWidget>
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TextAutoGenerateListView;
/**
 * @brief The TextAutoGenerateResultWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateResultWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateResultWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateResultWidget() override;

    void handleKeyPressEvent(QKeyEvent *ev);
    void editingFinished(const QByteArray &uuid);

    [[nodiscard]] int scrollbarPosition() const;
    void setScrollbarPosition(int position);
    void scrollToBottom();

    [[nodiscard]] int scrollbarPositionMaximum() const;
Q_SIGNALS:
    void editMessageRequested(const QModelIndex &index);
    void cancelRequested(const QByteArray &uuid);
    void refreshAnswerRequested(const QByteArray &charId, const QModelIndex &index);
    void switchToChat(const QByteArray &uuid);

private:
    TextAutoGenerateListView *const mTextAutoGenerateListView;
};

}
