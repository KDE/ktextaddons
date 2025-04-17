/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratelistviewdelegate.h"
#include "core/textautogeneratechatmodel.h"
#include "textautogeneratedelegateutils.h"
#include "textautogeneratelistviewtextselection.h"
#include "textautogeneratetextwidget_debug.h"
#include <QListView>
#include <QPainter>
#include <QTextFrame>
#include <QTextFrameFormat>
#include <QToolTip>
#include <qabstracttextdocumentlayout.h>
// #define DEBUG_PAINTING
using namespace TextAutogenerateText;
TextAutogenerateListViewDelegate::TextAutogenerateListViewDelegate(QListView *view)
    : QItemDelegate{view}
    , mListView(view)
    , mTextSelection(new TextAutogenerateListViewTextSelection(this, this))
{
    mSizeHintCache.setMaxEntries(32);
    connect(mTextSelection, &TextAutogenerateListViewTextSelection::repaintNeeded, this, &TextAutogenerateListViewDelegate::updateView);
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
    if (mTextSelection) {
        const QList<QAbstractTextDocumentLayout::Selection> selections = TextAutogenerateDelegateUtils::selection(mTextSelection, doc, index, option);
        // Same as pDoc->drawContents(painter, clip) but we also set selections
        ctx.selections = selections;
        if (clip.isValid()) {
            painter->setClipRect(clip);
            ctx.clip = clip;
        }
    }
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

void TextAutogenerateListViewDelegate::clearCache()
{
    mSizeHintCache.clear();
    mDocumentCache.clear();
}

void TextAutogenerateListViewDelegate::clearSizeHintCache()
{
    mSizeHintCache.clear();
}

void TextAutogenerateListViewDelegate::removeMessageCache(const QByteArray &uuid)
{
    mDocumentCache.remove(uuid);
    mSizeHintCache.remove(uuid);
}

TextAutogenerateListViewDelegate::MessageLayout TextAutogenerateListViewDelegate::doLayout(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    TextAutogenerateListViewDelegate::MessageLayout layout;
    QRect usableRect = option.rect;
    const TextAutoGenerateMessage::Sender sender = index.data(TextAutoGenerateChatModel::SenderRole).value<TextAutoGenerateMessage::Sender>();
    const int indent = (sender == TextAutoGenerateMessage::Sender::User) ? 80 : 30;
    const int maxWidth = qMax(30, option.rect.width() - 2 * indent);
    const QSize textSize = sizeHint(index, maxWidth, option, &layout.baseLine);
    layout.textRect = QRect(indent, usableRect.top(), maxWidth, textSize.height());
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

void TextAutogenerateListViewDelegate::selectAll(const QStyleOptionViewItem &option, const QModelIndex &index)
{
    Q_UNUSED(option);
    mTextSelection->selectMessage(index);
    mListView->update(index);
    TextAutogenerateDelegateUtils::setClipboardSelection(mTextSelection);
}

bool TextAutogenerateListViewDelegate::mouseEvent(QEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    const QEvent::Type eventType = event->type();
    if (eventType == QEvent::MouseButtonRelease) {
        auto mev = static_cast<QMouseEvent *>(event);
        const TextAutogenerateListViewDelegate::MessageLayout layout = doLayout(option, index);
        if (handleMouseEvent(mev, layout.textRect, option, index)) {
            return true;
        }
    } else if (eventType == QEvent::MouseButtonPress || eventType == QEvent::MouseMove || eventType == QEvent::MouseButtonDblClick) {
        auto mev = static_cast<QMouseEvent *>(event);
        if (mev->buttons() & Qt::LeftButton) {
            const TextAutogenerateListViewDelegate::MessageLayout layout = doLayout(option, index);
            if (handleMouseEvent(mev, layout.textRect, option, index)) {
                return true;
            }
        }
    }
    return false;
}

bool TextAutogenerateListViewDelegate::helpEvent(QHelpEvent *helpEvent, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (!index.isValid()) {
        return false;
    }
    if (helpEvent->type() == QEvent::ToolTip) {
        const TextAutogenerateListViewDelegate::MessageLayout layout = doLayout(option, index);
        const QPoint helpEventPos{helpEvent->pos()};
        if (layout.textRect.contains(helpEventPos)) {
            const auto *doc = documentForIndex(index, layout.textRect.width());
            if (!doc) {
                return false;
            }

            const QPoint pos = helpEvent->pos() - layout.textRect.topLeft();
            QString formattedTooltip;
            if (TextAutogenerateDelegateUtils::generateToolTip(doc, pos, formattedTooltip)) {
                QToolTip::showText(helpEvent->globalPos(), formattedTooltip, view);
                return true;
            }

            return true;
        }
    }
    return false;
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
QString TextAutogenerateListViewDelegate::selectedText() const
{
    return mTextSelection->selectedText(TextAutogenerateListViewTextSelection::Format::Text);
}

bool TextAutogenerateListViewDelegate::hasSelection() const
{
    return mTextSelection->hasSelection();
}

bool TextAutogenerateListViewDelegate::handleMouseEvent(QMouseEvent *mouseEvent,
                                                        QRect messageRect,
                                                        const QStyleOptionViewItem &option,
                                                        const QModelIndex &index)
{
    Q_UNUSED(option)
    if (!messageRect.contains(mouseEvent->pos())) {
        return false;
    }

    const QPoint pos = mouseEvent->pos() - messageRect.topLeft();
    const QEvent::Type eventType = mouseEvent->type();

    // Text selection
    switch (eventType) {
#if 1
    case QEvent::MouseButtonPress:
        // TODO mTextSelectionImpl->setMightStartDrag(false);
        if (const auto *doc = documentForIndex(index, messageRect.width())) {
            const int charPos = doc->documentLayout()->hitTest(pos, Qt::FuzzyHit);
            qCDebug(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "pressed at pos" << charPos;
            if (charPos == -1) {
                return false;
            }
            if (mTextSelection->contains(index, charPos) && doc->documentLayout()->hitTest(pos, Qt::ExactHit) != -1) {
                // TODO mTextSelectionImpl->setMightStartDrag(true);
                return true;
            }

            // QWidgetTextControl also has code to support selectBlockOnTripleClick, shift to extend selection
            // (look there if you want to add these things)

            mTextSelection->setTextSelectionStart(index, charPos);
            return true;
        } else {
            mTextSelection->clear();
        }
        break;
    case QEvent::MouseMove:
#if 0
        if (!mTextSelectionImpl->mightStartDrag()) {
#endif
        if (const auto *doc = documentForIndex(index, messageRect.width())) {
            const int charPos = doc->documentLayout()->hitTest(pos, Qt::FuzzyHit);
            if (charPos != -1) {
                // QWidgetTextControl also has code to support isPreediting()/commitPreedit(), selectBlockOnTripleClick
                mTextSelection->setTextSelectionEnd(index, charPos);
                return true;
            }
        }
#if 0
        }
#endif
        break;
    case QEvent::MouseButtonRelease:
        qCDebug(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "released";
        TextAutogenerateDelegateUtils::setClipboardSelection(mTextSelection);
        // Clicks on links
        if (!mTextSelection->hasSelection()) {
            if (const auto *doc = documentForIndex(index, messageRect.width())) {
                const QString link = doc->documentLayout()->anchorAt(pos);
                if (!link.isEmpty()) {
                    // TODO Q_EMIT mRocketChatAccount->openLinkRequested(link);
                    return true;
                }
            }
        }
#if 0
        } else if (mTextSelectionImpl->mightStartDrag()) {
            // clicked into selection, didn't start drag, clear it (like kwrite and QTextEdit)
            mTextSelection->clear();
        }
#endif
        // don't return true here, we need to send mouse release events to other helpers (ex: click on image)
        break;
#endif
    case QEvent::MouseButtonDblClick:
        if (!mTextSelection->hasSelection()) {
            qDebug() << " DOUBLE CLICK";
            if (const auto *doc = documentForIndex(index, messageRect.width())) {
                const int charPos = doc->documentLayout()->hitTest(pos, Qt::FuzzyHit);
                qCDebug(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "double-clicked at pos" << charPos;
                if (charPos == -1) {
                    return false;
                }
                mTextSelection->selectWordUnderCursor(index, charPos);
                return true;
            }
        }
        break;
    default:
        break;
    }

    return false;
}
#include "moc_textautogeneratelistviewdelegate.cpp"
