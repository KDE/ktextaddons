/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QWidget>
class QLineEdit;
namespace TextAutogenerateText
{
class TextAutogenerateHistoryListView;
/**
 * @brief The TextAutogenerateHistoryWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutogenerateHistoryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutogenerateHistoryWidget(QWidget *parent = nullptr);
    ~TextAutogenerateHistoryWidget() override;

Q_SIGNALS:
    void goToDiscussion(const QByteArray &uuid);

private:
    TextAutogenerateHistoryListView *const mTextAutogenerateHistoryListView;
    QLineEdit *const mSearchLineEdit;
};
}
