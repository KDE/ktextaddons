/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QWidget>
namespace TextAutogenerateText
{
class TextAutogenerateListView;
class TextAutoGenerateMessage;
/**
 * @brief The TextAutogenerateResultWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutogenerateResultWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutogenerateResultWidget(QWidget *parent = nullptr);
    ~TextAutogenerateResultWidget() override;

    void handleKeyPressEvent(QKeyEvent *ev);

Q_SIGNALS:
    void editMessage(const QModelIndex &index);

private:
    TextAutogenerateListView *const mTextAutogenerateListView;
};

}
