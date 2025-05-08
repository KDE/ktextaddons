/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QIdentityProxyModel>
namespace TextAutoGenerateText
{
class TextAutoGenerateHistoryModel : public QIdentityProxyModel
{
    Q_OBJECT
public:
    explicit TextAutoGenerateHistoryModel(QObject *parent = nullptr);
    ~TextAutoGenerateHistoryModel() override;

    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
};
}
