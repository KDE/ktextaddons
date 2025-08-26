/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateattachmentdelegatehelperimage.h"
#include "textautogeneratetext_export.h"
#include "widgets/view/lrucache.h"
#include <QItemDelegate>
#include <QScopedPointer>
#include <QTextDocument>
#include <memory>
class QListView;
namespace TextAutoGenerateText
{
class TextAutoGenerateListViewTextSelection;
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateListViewBaseDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit TextAutoGenerateListViewBaseDelegate(QListView *view);
    ~TextAutoGenerateListViewBaseDelegate() override;

    void clearSizeHintCache();

    void removeMessageCache(const QByteArray &uuid);

    void clearCache();

    [[nodiscard]] virtual QTextDocument *documentForIndex(const QModelIndex &index, int width) const = 0;
    [[nodiscard]] QString selectedText() const;
    [[nodiscard]] bool hasSelection() const;
    [[nodiscard]] virtual bool mouseEvent(QEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index);
    [[nodiscard]] virtual bool maybeStartDrag(QMouseEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index);
    [[nodiscard]] QString urlAt(const QModelIndex &index, QPoint pos) const;

    void selectAll(const QStyleOptionViewItem &option, const QModelIndex &index);

    void clearSelection();

Q_SIGNALS:
    void updateView(const QModelIndex &index);

protected:
    [[nodiscard]] QSize documentSizeHint(const QModelIndex &index, int maxWidth, const QStyleOptionViewItem &option, qreal *pBaseLine) const;
    [[nodiscard]] QSize textSizeHint(QTextDocument *doc, qreal *pBaseLine) const;
    [[nodiscard]] std::unique_ptr<QTextDocument> createTextDocument(const QString &text, int width) const;

    // Cache SizeHint value
    // We need to clear it when we resize widget.
    mutable LRUCache<QByteArray, QSize> mSizeHintCache;

    mutable LRUCache<QByteArray, std::unique_ptr<QTextDocument>> mDocumentCache;
    QAbstractItemView *const mListView;
    TextAutoGenerateListViewTextSelection *const mTextSelection;
    QScopedPointer<TextAutoGenerateAttachmentDelegateHelperImage> mHelperImage;
};
}
