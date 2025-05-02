/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QAbstractProxyModel>
namespace TextAutogenerateText
{
class TextAutoGenerateHistoryListHeadingsProxyModel : public QAbstractProxyModel
{
public:
    explicit TextAutoGenerateHistoryListHeadingsProxyModel(QObject *parent = nullptr);
    ~TextAutoGenerateHistoryListHeadingsProxyModel() override;
};

}
