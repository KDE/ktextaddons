/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QSortFilterProxyModel>

class OllamaModelInfosSortProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit OllamaModelInfosSortProxyModel(QObject *parent = nullptr);
    ~OllamaModelInfosSortProxyModel() override;
};
