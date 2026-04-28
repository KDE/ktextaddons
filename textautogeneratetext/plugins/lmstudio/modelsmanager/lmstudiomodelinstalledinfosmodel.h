/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "lmstudiomodelinstalledinfo.h"
#include "plugincommonmodelinstalledinfosmodel.h"

#include <QAbstractListModel>

class LMStudioModelInstalledInfosModel : public PluginCommonModelInstalledInfosModel<LMStudioModelInstalledInfo>
{
    Q_OBJECT
public:
    enum ModelInfoRoles {
        Publisher = PluginCommonModelInstalledInfosModelBase::ModelInfoRoles::Categories + 1,
    };
    Q_ENUM(ModelInfoRoles)

    explicit LMStudioModelInstalledInfosModel(QObject *parent = nullptr);
    ~LMStudioModelInstalledInfosModel() override;

    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
};
