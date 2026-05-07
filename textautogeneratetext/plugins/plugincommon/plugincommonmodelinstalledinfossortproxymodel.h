/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogenerateplugincommon_export.h"

#include <QSortFilterProxyModel>
#include <TextAutoGenerateText/TextAutoGenerateManager>

class TEXTAUTOGENERATEPLUGINCOMMON_EXPORT PluginCommonModelInstalledInfosSortProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit PluginCommonModelInstalledInfosSortProxyModel(QObject *parent = nullptr);
    ~PluginCommonModelInstalledInfosSortProxyModel() override;

    [[nodiscard]] QList<TextAutoGenerateText::TextAutoGenerateManager::Category> categories() const;
    void setCategories(const QList<TextAutoGenerateText::TextAutoGenerateManager::Category> &newCategories);

protected:
    [[nodiscard]] bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    QList<TextAutoGenerateText::TextAutoGenerateManager::Category> mCategories;
};
