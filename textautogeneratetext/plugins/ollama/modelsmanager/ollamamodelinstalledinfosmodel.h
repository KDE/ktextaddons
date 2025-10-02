/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "ollamamodelinstalledinfo.h"

#include <QAbstractListModel>

class OllamaModelInstalledInfosModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ModelInfoRoles {
        ModelGeneratedName = Qt::UserRole + 1,
        OriginalName,
        Name,
        Description,
        Family,
        QuantizationLevel,
        ParameterSize,
        DescriptionInfo,
        Categories,
    };
    Q_ENUM(ModelInfoRoles)

    explicit OllamaModelInstalledInfosModel(QObject *parent = nullptr);
    ~OllamaModelInstalledInfosModel() override;

    [[nodiscard]] QList<OllamaModelInstalledInfo> modelInstalledInfos() const;
    void setModelInstalledInfos(const QList<OllamaModelInstalledInfo> &newModelInfos);

    [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

private:
    QList<OllamaModelInstalledInfo> mModelInstalledInfos;
};
