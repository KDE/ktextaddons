/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "libbergamot_private_export.h"
#include <QSortFilterProxyModel>

class LIBBERGAMOT_TESTS_EXPORT TranslatorProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit TranslatorProxyModel(QObject *parent = nullptr);
    ~TranslatorProxyModel() override;

    [[nodiscard]] QString searchString() const;
    void setSearchString(const QString &newSearchString);

protected:
    [[nodiscard]] bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    QString mSearchString;
};
