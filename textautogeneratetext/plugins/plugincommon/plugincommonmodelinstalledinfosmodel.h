/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogenerateplugincommon_export.h"

#include <QAbstractListModel>

class TEXTAUTOGENERATEPLUGINCOMMON_EXPORT PluginCommonModelInstalledInfosModel : public QAbstractListModel
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

    explicit PluginCommonModelInstalledInfosModel(QObject *parent = nullptr);
    ~PluginCommonModelInstalledInfosModel() override;
};
