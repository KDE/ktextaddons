/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "ollamamodelinstalledinfo.h"
#include "plugincommonmodelinstalledinfosmodel.h"

#include <QAbstractListModel>

class OllamaModelInstalledInfosModel : public PluginCommonModelInstalledInfosModel<OllamaModelInstalledInfo>
{
    Q_OBJECT
public:
    enum ModelInfoRoles {
        ModelGeneratedName = PluginCommonModelInstalledInfosModelBase::ModelInfoRoles::Categories + 1,
        Family,
        Languages,
    };
    Q_ENUM(ModelInfoRoles)

    explicit OllamaModelInstalledInfosModel(QObject *parent = nullptr);
    ~OllamaModelInstalledInfosModel() override;

    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
};
