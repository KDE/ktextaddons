/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "lrucache.h"
#include <QItemDelegate>
#include <QTextDocument>
#include <memory>

namespace TextAutogenerateText
{
class TextAutogenerateListViewDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit TextAutogenerateListViewDelegate(QObject *parent = nullptr);
    ~TextAutogenerateListViewDelegate() override;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    [[nodiscard]] QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void clearSizeHintCache();

private:
    // Cache SizeHint value
    // We need to clear it when we resize widget.
    mutable LRUCache<QByteArray, QSize> mSizeHintCache;

    mutable LRUCache<QByteArray, std::unique_ptr<QTextDocument>> mDocumentCache;
};
}
