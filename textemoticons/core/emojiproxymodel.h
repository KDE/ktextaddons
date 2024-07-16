/*
   SPDX-FileCopyrightText: 2021-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "textemoticonscore_export.h"
#include <QSortFilterProxyModel>
#include <memory>
namespace TextEmoticonsCore
{
/**
 * @brief The EmojiProxyModel class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTEMOTICONSCORE_EXPORT EmojiProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

    Q_PROPERTY(QString category READ category WRITE setCategory NOTIFY categoryChanged)

public:
    explicit EmojiProxyModel(QObject *parent = nullptr);
    ~EmojiProxyModel() override;
    [[nodiscard]] QString category() const;
    void setCategory(const QString &newCategories);

    [[nodiscard]] QStringList recentEmoticons() const;
    void setRecentEmoticons(const QStringList &newRecentEmoticons);

    [[nodiscard]] QString searchIdentifier() const;
    void setSearchIdentifier(const QString &newSearchIdentifier);

Q_SIGNALS:
    void categoryChanged();

protected:
    [[nodiscard]] bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
    [[nodiscard]] bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private:
    class EmojiProxyModelPrivate;
    std::unique_ptr<EmojiProxyModelPrivate> const d;
};
}
