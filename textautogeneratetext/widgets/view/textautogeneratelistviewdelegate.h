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
    struct MessageLayout {
        // Text message
        QRect textRect;
        qreal baseLine; // used to draw sender/timestamp
    };

    [[nodiscard]] QSize sizeHint(const QModelIndex &index, int maxWidth, const QStyleOptionViewItem &option, qreal *pBaseLine) const;
    [[nodiscard]] QSize textSizeHint(QTextDocument *doc, qreal *pBaseLine) const;
    [[nodiscard]] TextAutogenerateListViewDelegate::MessageLayout doLayout(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    [[nodiscard]] QTextDocument *documentForIndex(const QModelIndex &index, int width) const;
    [[nodiscard]] std::unique_ptr<QTextDocument> createTextDocument(const QString &text, int width) const;
    // Cache SizeHint value
    // We need to clear it when we resize widget.
    mutable LRUCache<QByteArray, QSize> mSizeHintCache;

    mutable LRUCache<QByteArray, std::unique_ptr<QTextDocument>> mDocumentCache;
};
}
