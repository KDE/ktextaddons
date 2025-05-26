/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "ollamamodelavailableinfo.h"
#include "textautogenerateollama_private_export.h"
#include <QSortFilterProxyModel>

class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelAvailableInfosSortProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit OllamaModelAvailableInfosSortProxyModel(QObject *parent = nullptr);
    ~OllamaModelAvailableInfosSortProxyModel() override;

    [[nodiscard]] QList<OllamaModelAvailableInfo::Category> categories() const;
    void setCategories(const QList<OllamaModelAvailableInfo::Category> &newCategories);

protected:
    [[nodiscard]] bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    QList<OllamaModelAvailableInfo::Category> mCategories;
};
