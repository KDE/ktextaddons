/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "ollamamodelinfo.h"

#include <QAbstractListModel>

class OllamaModelInfosModel : public QAbstractListModel
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
    };
    Q_ENUM(ModelInfoRoles)

    explicit OllamaModelInfosModel(QObject *parent = nullptr);
    ~OllamaModelInfosModel() override;

    [[nodiscard]] QList<OllamaModelInfo> modelInfos() const;
    void setModelInfos(const QList<OllamaModelInfo> &newModelInfos);

    [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

private:
    QList<OllamaModelInfo> mModelInfos;
};
