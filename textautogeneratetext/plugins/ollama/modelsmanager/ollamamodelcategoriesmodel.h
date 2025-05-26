/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "ollamamodelinfo.h"
#include "textautogenerateollama_private_export.h"
#include <QStandardItemModel>

class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelCategoriesModel : public QStandardItemModel
{
    Q_OBJECT
public:
    struct CategoryInfo {
        OllamaModelInfo::Category identifier;
        QString name;
    };

    enum CategoriesRoles {
        Identifier = Qt::UserRole + 1,
        Title,
    };
    Q_ENUM(CategoriesRoles)

    explicit OllamaModelCategoriesModel(QObject *parent = nullptr);
    ~OllamaModelCategoriesModel() override;

    [[nodiscard]] QList<CategoryInfo> categories() const;

    [[nodiscard]] QList<OllamaModelInfo::Category> categoriesSelected() const;

private:
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void createItem(const QString &displayStr, OllamaModelInfo::Category identifier);
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void fillCategories();
    QList<CategoryInfo> mCategories;
};
Q_DECLARE_TYPEINFO(OllamaModelCategoriesModel::CategoryInfo, Q_RELOCATABLE_TYPE);
