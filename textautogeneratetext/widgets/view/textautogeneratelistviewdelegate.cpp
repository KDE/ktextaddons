/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratelistviewdelegate.h"
#include "core/textautogeneratechatmodel.h"
#include "textautogeneratetextwidget_debug.h"
#include <QPainter>
#include <QTextFrame>
#include <QTextFrameFormat>
#include <qabstracttextdocumentlayout.h>

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

    const MessageLayout layout = doLayout(option, index);
    if (layout.textRect.isValid()) {
#ifdef DEBUG_PAINTING
        painter->save();
        painter->setPen(QPen(Qt::red));
        painter->drawRect(layout.textRect);
        painter->restore();
#endif
        draw(painter, layout.textRect, index, option);
    }
}

void TextAutogenerateListViewDelegate::draw(QPainter *painter, QRect rect, const QModelIndex &index, const QStyleOptionViewItem &option) const
{
    auto *doc = documentForIndex(index, rect.width());
    if (!doc) {
        return;
    }
    painter->save();
    painter->translate(rect.left(), rect.top());
    const QRect clip(0, 0, rect.width(), rect.height());

    QAbstractTextDocumentLayout::PaintContext ctx;
    /*
    if (selection) {
        const QList<QAbstractTextDocumentLayout::Selection> selections =
            MessageDelegateUtils::selection(selection, doc, index, option, msgAttach, msgUrl, isAMessage);
        // Same as pDoc->drawContents(painter, clip) but we also set selections
        ctx.selections = selections;
        if (clip.isValid()) {
            painter->setClipRect(clip);
            ctx.clip = clip;
        }
    }
    */
    doc->documentLayout()->draw(painter, ctx);
    painter->restore();
}

QSize TextAutogenerateListViewDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const QByteArray uuid = index.data(TextAutoGenerateChatModel::UuidRole).toByteArray();
    auto it = mSizeHintCache.find(uuid);
    if (it != mSizeHintCache.end()) {
        const QSize result = it->value;
        qCDebug(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "TextAutogenerateListViewDelegate: SizeHint found in cache: " << result;
        return result;
    }

    const TextAutogenerateListViewDelegate::MessageLayout layout = doLayout(option, index);
    const QSize size = {layout.textRect.width(), layout.textRect.height()};
    if (!size.isEmpty()) {
        mSizeHintCache.insert(uuid, size);
    }
    return size;
}

void TextAutogenerateListViewDelegate::clearSizeHintCache()
{
    mSizeHintCache.clear();
}

void TextAutogenerateListViewDelegate::removeMessageCache(const QByteArray &uuid)
{
    mDocumentCache.remove(uuid);
}

TextAutogenerateListViewDelegate::MessageLayout TextAutogenerateListViewDelegate::doLayout(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    TextAutogenerateListViewDelegate::MessageLayout layout;
    QRect usableRect = option.rect;
    const int maxWidth = qMax(30, option.rect.width() /* - textLeft - widthAfterMessage*/);
    const QSize textSize = sizeHint(index, maxWidth, option, &layout.baseLine);
    // TODO customize
    static int indent = 30;
    const TextAutoGenerateMessage::Sender sender = index.data(TextAutoGenerateChatModel::SenderRole).value<TextAutoGenerateMessage::Sender>();

    layout.textRect = QRect(sender == TextAutoGenerateMessage::Sender::User ? 80 : indent, usableRect.top(), maxWidth, textSize.height());
    return layout;
}

QSize TextAutogenerateListViewDelegate::sizeHint(const QModelIndex &index, int maxWidth, const QStyleOptionViewItem &option, qreal *pBaseLine) const
{
    Q_UNUSED(option)
    auto *doc = documentForIndex(index, maxWidth);
    return textSizeHint(doc, pBaseLine);
}

QSize TextAutogenerateListViewDelegate::textSizeHint(QTextDocument *doc, qreal *pBaseLine) const
{
    if (!doc) {
        return {};
    }
    const QSize size(doc->idealWidth(), doc->size().height()); // do the layouting, required by lineAt(0) below

    const QTextLine &line = doc->firstBlock().layout()->lineAt(0);
    *pBaseLine = line.y() + line.ascent(); // relative
    // qDebug() << " doc->" << doc->toPlainText() << " size " << size;
    return size;
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
