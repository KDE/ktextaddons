/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QItemDelegate>

namespace TextAutogenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutogenerateHistoryListViewDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit TextAutogenerateHistoryListViewDelegate(QObject *parent = nullptr);
    ~TextAutogenerateHistoryListViewDelegate() override;

    [[nodiscard]] bool helpEvent(QHelpEvent *helpEvent, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index) override;
};
}
