/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QItemDelegate>
#include <QObject>

namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateSearchListViewDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSearchListViewDelegate(QObject *parent = nullptr);
    ~TextAutoGenerateSearchListViewDelegate() override;
};
}
