/*
   SPDX-FileCopyrightText: 2021 David Faure <faure@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogeneratelistviewtextselection.h"
using namespace Qt::Literals::StringLiterals;

#include "textautogeneratelistviewdelegate.h"

#include <QTextCursor>
#include <QTextDocument>
#include <QTextDocumentFragment>
using namespace TextAutoGenerateText;

TextAutoGenerateListViewTextSelection::TextAutoGenerateListViewTextSelection(TextAutoGenerateListViewBaseDelegate *delegate, QObject *parent)
    : QObject(parent)
    , mDelegate(delegate)
{
}

bool TextAutoGenerateListViewTextSelection::hasSelection() const
{
    return mStartIndex.isValid() && mEndIndex.isValid() && ((mStartPos > -1 && mEndPos > -1 && mStartPos != mEndPos));
}

TextAutoGenerateListViewTextSelection::OrderedPositions TextAutoGenerateListViewTextSelection::orderedPositions() const
{
    Q_ASSERT(!mStartIndex.isValid() || !mEndIndex.isValid() || mStartIndex.model() == mEndIndex.model());
    TextAutoGenerateListViewTextSelection::OrderedPositions ret{mStartIndex.row(), mStartPos, mEndIndex.row(), mEndPos};
    if (ret.fromRow > ret.toRow) {
        std::swap(ret.fromRow, ret.toRow);
        std::swap(ret.fromCharPos, ret.toCharPos);
    }
    return ret;
}

QTextCursor TextAutoGenerateListViewTextSelection::selectionForIndex(const QModelIndex &index, QTextDocument *doc) const
{
    if (!hasSelection()) {
        return {};
    }
    Q_ASSERT(index.model() == mStartIndex.model());
    Q_ASSERT(index.model() == mEndIndex.model());

    const OrderedPositions ordered = orderedPositions();
    int fromCharPos = ordered.fromCharPos;
    // qDebug() << "BEFORE toCharPos" << toCharPos << " fromCharPos " << fromCharPos;
    QTextCursor cursor(doc);

    // qDebug() << "AFTER toCharPos" << toCharPos << " fromCharPos " << fromCharPos;
    const int row = index.row();
    if (row == ordered.fromRow)
        cursor.setPosition(qMax(fromCharPos, 0));
    else if (row > ordered.fromRow)
        cursor.setPosition(0);
    else
        return {};
    if (row == ordered.toRow) {
        const int toCharPos = ordered.toCharPos;
        cursor.setPosition(qMax(toCharPos, 0), QTextCursor::KeepAnchor);
    } else if (row < ordered.toRow)
        cursor.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
    else
        return {};
    return cursor;
}

void TextAutoGenerateListViewTextSelection::selectionText(const OrderedPositions ordered,
                                                          Format format,
                                                          int row,
                                                          const QModelIndex &index,
                                                          QTextDocument *doc,
                                                          QString &str) const
{
    const QTextCursor cursor = selectionForIndex(index, doc);
    const QTextDocumentFragment fragment(cursor);
    str += format == Format::Text ? fragment.toPlainText() : fragment.toHtml();
    if (row < ordered.toRow) {
        str += u'\n';
    }
}

QString TextAutoGenerateListViewTextSelection::selectedText(Format format) const
{
    if (!hasSelection()) {
        return {};
    }
    const OrderedPositions ordered = orderedPositions();
    QString str;
    for (int row = ordered.fromRow; row <= ordered.toRow; ++row) {
        const QModelIndex index = QModelIndex(mStartIndex).siblingAtRow(row);
        QTextDocument *doc = mDelegate->documentForIndex(index, -1);
        if (doc) {
            selectionText(ordered, format, row, index, doc, str);
        }
    }
    return str;
}

bool TextAutoGenerateListViewTextSelection::contains(const QModelIndex &index, int charPos) const
{
    if (!hasSelection()) {
        return false;
    }
    Q_ASSERT(index.model() == mStartIndex.model());
    const int row = index.row();
    const OrderedPositions ordered = orderedPositions();
    if (row == ordered.fromRow) {
        if (row == ordered.toRow) // single line selection
            return ordered.fromCharPos <= charPos && charPos <= ordered.toCharPos;
        return ordered.fromCharPos <= charPos;
    } else if (row == ordered.toRow) {
        return charPos <= ordered.toCharPos;
    } else {
        return row > ordered.fromRow && row < ordered.toRow;
    }
}

void TextAutoGenerateListViewTextSelection::clear()
{
    const QModelIndex index = mStartIndex;
    const OrderedPositions ordered = orderedPositions();

    mStartIndex = QPersistentModelIndex{};
    mEndIndex = QPersistentModelIndex{};
    mStartPos = -1;
    mEndPos = -1;

    // Repaint indexes that are no longer selected
    if (ordered.fromRow > -1) {
        if (ordered.toRow > -1) {
            for (int row = ordered.fromRow; row <= ordered.toRow; ++row) {
                Q_EMIT repaintNeeded(index.siblingAtRow(row));
            }
        } else {
            Q_EMIT repaintNeeded(index);
        }
    }
}

void TextAutoGenerateListViewTextSelection::setTextSelectionStart(const QModelIndex &index, int charPos)
{
    clear();
    Q_ASSERT(index.isValid());
    mStartIndex = index;
    mStartPos = charPos;
}

void TextAutoGenerateListViewTextSelection::setTextSelectionEnd(const QModelIndex &index, int charPos)
{
    int from = mEndIndex.row();
    int to = index.row();
    if (from != -1 && from != to) {
        mEndIndex = index;

        if (from > to) { // reducing (moving the end up)
            std::swap(from, to);
            ++from; // 'from' is @p index, it's under the mouse anyway
        } else { // extending (moving the down)
            --to; // 'to' is @p index, it's under the mouse anyway
        }

        // Repaint indexes that are no longer selected
        // or that got selected when moving the mouse down fast
        for (int row = from; row <= to; ++row) {
            Q_EMIT repaintNeeded(index.siblingAtRow(row));
        }
    }
    Q_ASSERT(index.isValid());
    mEndIndex = index;
    mEndPos = charPos;
}

void TextAutoGenerateListViewTextSelection::selectWord(const QModelIndex &index, int charPos, QTextDocument *doc)
{
    QTextCursor cursor(doc);
    cursor.setPosition(charPos);
    clear();
    cursor.select(QTextCursor::WordUnderCursor);
    mStartIndex = index;
    mEndIndex = index;
    mStartPos = cursor.selectionStart();
    mEndPos = cursor.selectionEnd();
}

void TextAutoGenerateListViewTextSelection::selectWordUnderCursor(const QModelIndex &index, int charPos)
{
    QTextDocument *doc = mDelegate->documentForIndex(index, -1);
    selectWord(index, charPos, doc);
}

void TextAutoGenerateListViewTextSelection::selectMessage(const QModelIndex &index)
{
    Q_ASSERT(index.isValid());
    clear();
    mStartIndex = index;
    mEndIndex = index;
    mStartPos = 0;
    QTextDocument *doc = mDelegate->documentForIndex(index, -1);
    if (doc) {
        mEndPos = doc->characterCount() - 1;
    }
}

bool TextAutoGenerateListViewTextSelection::mightStartDrag() const
{
    return mMightStartDrag;
}

void TextAutoGenerateListViewTextSelection::setMightStartDrag(bool newMightStartDrag)
{
    mMightStartDrag = newMightStartDrag;
}

#include "moc_textautogeneratelistviewtextselection.cpp"
