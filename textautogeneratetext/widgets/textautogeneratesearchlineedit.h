/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_private_export.h"
#include <QLineEdit>
class QTimer;
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateSearchLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSearchLineEdit(QWidget *parent = nullptr);
    ~TextAutoGenerateSearchLineEdit() override;

Q_SIGNALS:
    void searchText(const QString &str);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotSearchTimerFired();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotSearchTextEdited();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotTextChanged(const QString &text);
    QTimer *const mSearchTimer;
};
}
