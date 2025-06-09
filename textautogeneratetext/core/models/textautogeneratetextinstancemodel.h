/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_export.h"
#include <QAbstractListModel>
namespace TextAutoGenerateText
{
/**
 * @brief The TextAutoGenerateTextInstanceModel class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextInstanceModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextInstanceModel(QObject *parent = nullptr);
    ~TextAutoGenerateTextInstanceModel() override;

    [[nodiscard]] int rowCount(const QModelIndex & = {}) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
};
}
