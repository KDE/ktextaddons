/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "ollamamodelavailableinfo.h"

#include <QAbstractListModel>

class OllamaModelAvailableInfosModel : public QAbstractListModel
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

    explicit OllamaModelAvailableInfosModel(QObject *parent = nullptr);
    ~OllamaModelAvailableInfosModel() override;

    [[nodiscard]] QList<OllamaModelAvailableInfo> modelInfos() const;
    void setModelInfos(const QList<OllamaModelAvailableInfo> &newModelInfos);

    [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

private:
    QList<OllamaModelAvailableInfo> mModelInfos;
};
