/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "plugincommonmodelinstalledinfo.h"
#include "textautogenerateplugincommon_export.h"
#include <QAbstractListModel>
#include <concepts>

class TEXTAUTOGENERATEPLUGINCOMMON_EXPORT PluginCommonModelInstalledInfosModelBase : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ModelInfoRoles {
        OriginalName = Qt::UserRole + 1,
        Name,
        Description,
        QuantizationLevel,
        ParameterSize,
        DescriptionInfo,
        Categories,
    };
    Q_ENUM(ModelInfoRoles)

    explicit PluginCommonModelInstalledInfosModelBase(QObject *parent = nullptr);
    ~PluginCommonModelInstalledInfosModelBase() override;
};

template<typename T>
    requires std::derived_from<T, PluginCommonModelInstalledInfo>
class PluginCommonModelInstalledInfosModel : public PluginCommonModelInstalledInfosModelBase
{
public:
    explicit PluginCommonModelInstalledInfosModel(QObject *parent = nullptr)
        : PluginCommonModelInstalledInfosModelBase(parent)
    {
    }

    ~PluginCommonModelInstalledInfosModel() override = default;

    [[nodiscard]] QList<T> modelInstalledInfos() const
    {
        return mModelInstalledInfos;
    }

    void setModelInstalledInfos(const QList<T> &newModelInfos)
    {
        beginResetModel();
        mModelInstalledInfos = newModelInfos;
        endResetModel();
    }

    [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override
    {
        if (parent.isValid()) {
            return 0; // flat model
        }
        return mModelInstalledInfos.count();
    }

    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override
    {
        const auto &info = mModelInstalledInfos.at(index.row());
        switch (role) {
        case ModelInfoRoles::DescriptionInfo:
            return QVariant::fromValue(info);
        case ModelInfoRoles::QuantizationLevel:
            return info.quantizationLevel();
        case ModelInfoRoles::ParameterSize:
            return info.parameterSize();
        case ModelInfoRoles::OriginalName:
            return info.model();
        case ModelInfoRoles::Name:
        case Qt::DisplayRole:
            return info.name();
        case ModelInfoRoles::Categories:
            return QVariant::fromValue(info.categories());
        default:
            break;
        }
        return {};
    }

protected:
    QList<T> mModelInstalledInfos;
};
