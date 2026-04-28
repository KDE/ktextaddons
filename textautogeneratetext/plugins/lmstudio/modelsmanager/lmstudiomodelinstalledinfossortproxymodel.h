/*
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QSortFilterProxyModel>

class LMStudioModelInstalledInfosSortProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit LMStudioModelInstalledInfosSortProxyModel(QObject *parent = nullptr);
    ~LMStudioModelInstalledInfosSortProxyModel() override;
};
