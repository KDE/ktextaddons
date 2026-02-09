/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textautogenerateollamacommon_export.h"
#include <QStandardItemModel>
#include <TextAutoGenerateText/TextAutoGenerateManager>

class TEXTAUTOGENERATEOLLAMACOMMON_EXPORT OllamaCommonModelCategoriesModel : public QStandardItemModel
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

    explicit OllamaCommonModelCategoriesModel(QObject *parent = nullptr);
    ~OllamaCommonModelCategoriesModel() override;

    [[nodiscard]] QList<CategoryInfo> categories() const;

    [[nodiscard]] QList<TextAutoGenerateText::TextAutoGenerateManager::Category> categoriesSelected() const;

private:
    TEXTAUTOGENERATEOLLAMACOMMON_NO_EXPORT void createItem(const QString &displayStr, TextAutoGenerateText::TextAutoGenerateManager::Category identifier);
    TEXTAUTOGENERATEOLLAMACOMMON_NO_EXPORT void fillCategories();
    QList<CategoryInfo> mCategories;
};
Q_DECLARE_TYPEINFO(OllamaCommonModelCategoriesModel::CategoryInfo, Q_RELOCATABLE_TYPE);
