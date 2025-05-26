/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "ollamamodelinfo.h"
#include "textautogenerateollama_private_export.h"
#include <QSortFilterProxyModel>

class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelInfosSortProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit OllamaModelInfosSortProxyModel(QObject *parent = nullptr);
    ~OllamaModelInfosSortProxyModel() override;

    [[nodiscard]] OllamaModelInfo::Categories categories() const;
    void setCategories(OllamaModelInfo::Categories newCategories);

protected:
    [[nodiscard]] bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    OllamaModelInfo::Categories mCategories = OllamaModelInfo::Category::Unknown;
};
