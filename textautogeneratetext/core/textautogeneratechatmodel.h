/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QAbstractListModel>
namespace TextAutogenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateChatModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ChatRole : uint8_t {
        // TODO
    };
    explicit TextAutoGenerateChatModel(QObject *parent = nullptr);
    ~TextAutoGenerateChatModel() override;

    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;
    [[nodiscard]] int rowCount(const QModelIndex & = {}) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
};
}
