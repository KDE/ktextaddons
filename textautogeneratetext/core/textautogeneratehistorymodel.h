/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_export.h"
#include <QAbstractListModel>
namespace TextAutogenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateHistoryModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum HistoryRole : uint8_t {
        Subject,
        Date,
        Model,
    };

    explicit TextAutoGenerateHistoryModel(QObject *parent = nullptr);
    ~TextAutoGenerateHistoryModel() override;

    [[nodiscard]] int rowCount(const QModelIndex & = {}) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
};
}
