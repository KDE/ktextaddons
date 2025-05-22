/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QAbstractProxyModel>

class OllamaModelInfosSortProxyModel : public QAbstractProxyModel
{
    Q_OBJECT
public:
    explicit OllamaModelInfosSortProxyModel(QObject *parent = nullptr);
    ~OllamaModelInfosSortProxyModel() override;
};
