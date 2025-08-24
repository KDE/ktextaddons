/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogenerateollama_private_export.h"
#include <QSortFilterProxyModel>
#include <TextAutoGenerateText/TextAutoGenerateManager>

class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelAvailableInfosSortProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit OllamaModelAvailableInfosSortProxyModel(QObject *parent = nullptr);
    ~OllamaModelAvailableInfosSortProxyModel() override;

    [[nodiscard]] QList<TextAutoGenerateText::TextAutoGenerateManager::Category> categories() const;
    void setCategories(const QList<TextAutoGenerateText::TextAutoGenerateManager::Category> &newCategories);

protected:
    [[nodiscard]] bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    QList<TextAutoGenerateText::TextAutoGenerateManager::Category> mCategories;
};
