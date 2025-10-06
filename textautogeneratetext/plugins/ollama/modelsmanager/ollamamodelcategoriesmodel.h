/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textautogenerateollama_private_export.h"
#include <QStandardItemModel>
#include <TextAutoGenerateText/TextAutoGenerateManager>

class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelCategoriesModel : public QStandardItemModel
{
    Q_OBJECT
public:
    struct CategoryInfo {
        TextAutoGenerateText::TextAutoGenerateManager::Category identifier;
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

    [[nodiscard]] QList<TextAutoGenerateText::TextAutoGenerateManager::Category> categoriesSelected() const;

private:
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void createItem(const QString &displayStr, TextAutoGenerateText::TextAutoGenerateManager::Category identifier);
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void fillCategories();
    QList<CategoryInfo> mCategories;
};
Q_DECLARE_TYPEINFO(OllamaModelCategoriesModel::CategoryInfo, Q_RELOCATABLE_TYPE);
