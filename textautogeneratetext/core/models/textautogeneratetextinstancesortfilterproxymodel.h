/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QSortFilterProxyModel>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextInstanceSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextInstanceSortFilterProxyModel(QObject *parent = nullptr);
    ~TextAutoGenerateTextInstanceSortFilterProxyModel() override;

    QString searchText() const;
    void setSearchText(const QString &newSearchText);

protected:
    [[nodiscard]] bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    QString mSearchText;
};
}
