/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textautogenerateollama_private_export.h"
#include <QStandardItemModel>

class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelCategoriesModel : public QStandardItemModel
{
    Q_OBJECT
public:
    struct CategoryInfo {
        QString identifier;
        QString name;
    };

    enum CategoriesRoles {
        Identifier = Qt::UserRole + 1,
        Title,
    };
    Q_ENUM(CategoriesRoles)

    explicit OllamaModelCategoriesModel(QObject *parent = nullptr);
    ~OllamaModelCategoriesModel() override;

    [[nodiscard]] QList<CategoryInfo> appsCategories() const;
    void setAppsCategories(const QList<CategoryInfo> &appsCategories);

    [[nodiscard]] bool wasFilled() const;

    [[nodiscard]] QStringList categoriesSelected() const;

private:
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void createItem(const QString &displayStr, const QString &identifier);
    QList<CategoryInfo> mAppsCategories;
};
