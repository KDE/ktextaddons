/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "libvoskspeechtotext_private_export.h"
#include <QSortFilterProxyModel>

class LIBVOSKSPEECHTOTEXT_TESTS_EXPORT VoskSpeechToTextProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit VoskSpeechToTextProxyModel(QObject *parent = nullptr);
    ~VoskSpeechToTextProxyModel() override;

    [[nodiscard]] QString searchString() const;
    void setSearchString(const QString &newSearchString);

protected:
    [[nodiscard]] bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

    [[nodiscard]] bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private:
    QString mSearchString;
};
