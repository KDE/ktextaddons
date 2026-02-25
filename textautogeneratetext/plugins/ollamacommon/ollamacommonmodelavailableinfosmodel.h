/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "ollamacommonmodelavailableinfo.h"
#include "textautogenerateollamacommon_export.h"

#include <QAbstractListModel>

class TEXTAUTOGENERATEOLLAMACOMMON_EXPORT OllamaCommonModelAvailableInfosModel : public QAbstractListModel
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
        AvailableInfo,
    };
    Q_ENUM(ModelInfoRoles)

    explicit OllamaCommonModelAvailableInfosModel(QObject *parent = nullptr);
    ~OllamaCommonModelAvailableInfosModel() override;

    [[nodiscard]] QList<OllamaCommonModelAvailableInfo> modelInfos() const;
    void setModelInfos(const QList<OllamaCommonModelAvailableInfo> &newModelInfos);

    [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

private:
    QList<OllamaCommonModelAvailableInfo> mModelInfos;
};
