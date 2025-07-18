/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratelistviewbasedelegate.h"
#include "textautogeneratelistviewtextselection.h"
#include "textautogeneratetextwidget_debug.h"
#include "widgets/view/textautogeneratedelegateutils.h"
#include <QAbstractTextDocumentLayout>
#include <QListView>
#include <QTextFrame>
#include <QTextFrameFormat>

using namespace TextAutoGenerateText;
TextAutoGenerateListViewBaseDelegate::TextAutoGenerateListViewBaseDelegate(QListView *view)
    : QItemDelegate{view}
    , mListView(view)
    , mTextSelection(new TextAutoGenerateListViewTextSelection(this, this))
{
    connect(mTextSelection, &TextAutoGenerateListViewTextSelection::repaintNeeded, this, &TextAutoGenerateListViewBaseDelegate::updateView);
    mSizeHintCache.setMaxEntries(32);
}

TextAutoGenerateListViewBaseDelegate::~TextAutoGenerateListViewBaseDelegate() = default;

void TextAutoGenerateListViewBaseDelegate::clearSelection()
{
    mTextSelection->clear();
}

void TextAutoGenerateListViewBaseDelegate::clearCache()
{
    clearSizeHintCache();
    mDocumentCache.clear();
}

void TextAutoGenerateListViewBaseDelegate::clearSizeHintCache()
{
    mSizeHintCache.clear();
}

void TextAutoGenerateListViewBaseDelegate::removeMessageCache(const QByteArray &uuid)
{
    mDocumentCache.remove(uuid);
    mSizeHintCache.remove(uuid);
}

std::unique_ptr<QTextDocument> TextAutoGenerateListViewBaseDelegate::createTextDocument(const QString &text, int width) const
{
    std::unique_ptr<QTextDocument> doc(new QTextDocument);
    // doc->setMarkdown(text);
    doc->setHtml(text);
    doc->setTextWidth(width);
    QTextFrame *frame = doc->frameAt(0);
    QTextFrameFormat frameFormat = frame->frameFormat();
    frameFormat.setMargin(0);
    frame->setFrameFormat(frameFormat);
    return doc;
}

bool TextAutoGenerateListViewBaseDelegate::mouseEvent(QEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    Q_UNUSED(event)
    Q_UNUSED(option)
    Q_UNUSED(index)
    return false;
}

bool TextAutoGenerateListViewBaseDelegate::maybeStartDrag(QMouseEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    Q_UNUSED(event)
    Q_UNUSED(option)
    Q_UNUSED(index)
    return false;
}

QString TextAutoGenerateListViewBaseDelegate::selectedText() const
{
    return mTextSelection->selectedText(TextAutoGenerateListViewTextSelection::Format::Text);
}

bool TextAutoGenerateListViewBaseDelegate::hasSelection() const
{
    return mTextSelection->hasSelection();
}

void TextAutoGenerateListViewBaseDelegate::selectAll(const QStyleOptionViewItem &option, const QModelIndex &index)
{
    Q_UNUSED(option);
    mTextSelection->selectMessage(index);
    mListView->update(index);
    TextAutoGenerateDelegateUtils::setClipboardSelection(mTextSelection);
}

QSize TextAutoGenerateListViewBaseDelegate::documentSizeHint(const QModelIndex &index, int maxWidth, const QStyleOptionViewItem &option, qreal *pBaseLine) const
{
    Q_UNUSED(option)
    auto *doc = documentForIndex(index, maxWidth);
    return textSizeHint(doc, pBaseLine);
}

QSize TextAutoGenerateListViewBaseDelegate::textSizeHint(QTextDocument *doc, qreal *pBaseLine) const
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

QString TextAutoGenerateListViewBaseDelegate::urlAt(const QModelIndex &index, QPoint pos) const
{
    auto document = documentForIndex(index, -1);
    if (!document) {
        return {};
    }
    return document->documentLayout()->anchorAt(pos);
}

#include "moc_textautogeneratelistviewbasedelegate.cpp"
