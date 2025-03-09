/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QStyledItemDelegate>
namespace TextAutogenerateText
{
class TextAutogenerateListViewDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit TextAutogenerateListViewDelegate(QObject *parent = nullptr);
    ~TextAutogenerateListViewDelegate() override;
};
}
