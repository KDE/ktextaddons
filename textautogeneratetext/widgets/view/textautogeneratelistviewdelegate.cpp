/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratelistviewdelegate.h"
#include "core/textautogeneratechatmodel.h"
#include <QPainter>
#include <QTextFrame>
#include <QTextFrameFormat>

using namespace TextAutogenerateText;
TextAutogenerateListViewDelegate::TextAutogenerateListViewDelegate(QObject *parent)
    : QItemDelegate{parent}
{
    mSizeHintCache.setMaxEntries(32);
}

TextAutogenerateListViewDelegate::~TextAutogenerateListViewDelegate() = default;

void TextAutogenerateListViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    drawBackground(painter, option, index);
    painter->restore();
    // TODO implement it
    QItemDelegate::paint(painter, option, index);
}

QSize TextAutogenerateListViewDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // TODO implement it.
    return QItemDelegate::sizeHint(option, index);
}

void TextAutogenerateListViewDelegate::clearSizeHintCache()
{
    mSizeHintCache.clear();
}

QTextDocument *TextAutogenerateListViewDelegate::documentForIndex(const QModelIndex &index, int width) const
{
    Q_ASSERT(index.isValid());
    const QByteArray uuid = index.data(TextAutoGenerateChatModel::UuidRole).toByteArray();
    Q_ASSERT(!uuid.isEmpty());
    auto it = mDocumentCache.find(uuid);
    if (it != mDocumentCache.end()) {
        auto ret = it->value.get();
        if (width != -1 && !qFuzzyCompare(ret->textWidth(), width)) {
            ret->setTextWidth(width);
        }
        return ret;
    }

    const QString text = index.data(TextAutoGenerateChatModel::MessageRole).toString();
    if (text.isEmpty()) {
        return nullptr;
    }
    auto doc = createTextDocument(text, width);
    auto ret = doc.get();
    mDocumentCache.insert(uuid, std::move(doc));
    return ret;
}

std::unique_ptr<QTextDocument> TextAutogenerateListViewDelegate::createTextDocument(const QString &text, int width) const
{
    std::unique_ptr<QTextDocument> doc(new QTextDocument);
    doc->setHtml(text);
    doc->setTextWidth(width);
    QTextFrame *frame = doc->frameAt(0);
    QTextFrameFormat frameFormat = frame->frameFormat();
    frameFormat.setMargin(0);
    frame->setFrameFormat(frameFormat);
    return doc;
}

#include "moc_textautogeneratelistviewdelegate.cpp"
