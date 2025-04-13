/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QStyledItemDelegate>

namespace TextAutogenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutogenerateHistoryListViewDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit TextAutogenerateHistoryListViewDelegate(QObject *parent = nullptr);
    ~TextAutogenerateHistoryListViewDelegate() override;
};
}
