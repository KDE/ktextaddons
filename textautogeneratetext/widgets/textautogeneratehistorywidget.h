/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QWidget>
class QLineEdit;
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TextAutoGenerateHistoryListView;
/**
 * @brief The TextAutoGenerateHistoryWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateHistoryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateHistoryWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateHistoryWidget() override;

Q_SIGNALS:
    void switchToChat(const QByteArray &uuid);

private:
    TextAutoGenerateHistoryListView *const mTextAutoGenerateHistoryListView;
    QLineEdit *const mSearchLineEdit;
};
}
