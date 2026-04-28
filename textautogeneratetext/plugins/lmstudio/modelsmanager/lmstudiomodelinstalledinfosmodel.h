/*
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "lmstudiomodelinstalledinfo.h"

#include <QAbstractListModel>

class LMStudioModelInstalledInfosModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ModelInfoRoles {
        ModelGeneratedName = Qt::UserRole + 1,
        OriginalName,
        Name,
        Description,
        QuantizationLevel,
        ParameterSize,
        DescriptionInfo,
        Categories,
    };
    Q_ENUM(ModelInfoRoles)

    explicit LMStudioModelInstalledInfosModel(QObject *parent = nullptr);
    ~LMStudioModelInstalledInfosModel() override;

    [[nodiscard]] QList<LMStudioModelInstalledInfo> modelInstalledInfos() const;
    void setModelInstalledInfos(const QList<LMStudioModelInstalledInfo> &newModelInfos);

    [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

private:
    QList<LMStudioModelInstalledInfo> mModelInstalledInfos;
};
