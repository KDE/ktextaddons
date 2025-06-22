/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "genericnetworkmodelavailableinfo.h"

#include <QAbstractListModel>

class GenericNetworkAvailableInfosModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ModelInfoRoles {
        ModelName = Qt::UserRole + 1,
        Description,
        Categories,
        CategoriesName,
        Author,
        Url,
        Tags,
        Languages,
    };
    Q_ENUM(ModelInfoRoles)

    explicit GenericNetworkAvailableInfosModel(QObject *parent = nullptr);
    ~GenericNetworkAvailableInfosModel() override;

    [[nodiscard]] QList<GenericNetworkModelAvailableInfo> modelInfos() const;
    void setModelInfos(const QList<GenericNetworkModelAvailableInfo> &newModelInfos);

    [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

private:
    QList<GenericNetworkModelAvailableInfo> mModelInfos;
};
