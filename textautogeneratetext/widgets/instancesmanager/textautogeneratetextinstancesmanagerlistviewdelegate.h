/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QStyledItemDelegate>
namespace TextAutoGenerateText
{
class TextAutoGenerateTextInstancesManagerListViewDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextInstancesManagerListViewDelegate(QObject *parent = nullptr);
    ~TextAutoGenerateTextInstancesManagerListViewDelegate() override;
};
}
