/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogenerateollamacommon_export.h"
#include <QSortFilterProxyModel>
#include <TextAutoGenerateText/TextAutoGenerateManager>

class TEXTAUTOGENERATEOLLAMACOMMON_EXPORT OllamaCommonModelAvailableInfosSortProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit OllamaCommonModelAvailableInfosSortProxyModel(QObject *parent = nullptr);
    ~OllamaCommonModelAvailableInfosSortProxyModel() override;

    [[nodiscard]] QList<TextAutoGenerateText::TextAutoGenerateManager::Category> categories() const;
    void setCategories(const QList<TextAutoGenerateText::TextAutoGenerateManager::Category> &newCategories);

protected:
    [[nodiscard]] bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    QList<TextAutoGenerateText::TextAutoGenerateManager::Category> mCategories;
};
