/*
   SPDX-FileCopyrightText: 2021 David Faure <faure@kde.org>
   SPDX-FileCopyrightText: 2024-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include <QObject>
#include <QPersistentModelIndex>

class QTextCursor;
class QTextDocument;
namespace TextAutoGenerateText
{
class TextAutoGenerateListViewBaseDelegate;
class TextAutoGenerateListViewTextSelection : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateListViewTextSelection(TextAutoGenerateListViewBaseDelegate *delegate, QObject *parent = nullptr);
    [[nodiscard]] bool hasSelection() const;
    enum class Format : uint8_t {
        Text,
        Html,
    };
    [[nodiscard]] QString selectedText(Format format) const;
    [[nodiscard]] bool contains(const QModelIndex &index, int charPos) const;
    [[nodiscard]] QTextCursor selectionForIndex(const QModelIndex &index, QTextDocument *doc) const;

    void clear();
    void setTextSelectionStart(const QModelIndex &index, int charPos);
    void setTextSelectionEnd(const QModelIndex &index, int charPos);
    void setAttachmentTextAutoGenerateListViewTextSelectionEnd(const QModelIndex &index, int charPos);
    void selectWordUnderCursor(const QModelIndex &index, int charPos);
    void selectMessage(const QModelIndex &index);

    [[nodiscard]] bool mightStartDrag() const;
    void setMightStartDrag(bool newMightStartDrag);

Q_SIGNALS:
    void repaintNeeded(const QModelIndex &index);

private:
    void selectWord(const QModelIndex &index, int charPos, QTextDocument *doc);
    struct OrderedPositions {
        int fromRow;
        int fromCharPos;
        int toRow;
        int toCharPos;
    };

    [[nodiscard]] OrderedPositions orderedPositions() const;
    void selectionText(const OrderedPositions ordered, Format format, int row, const QModelIndex &index, QTextDocument *doc, QString &str) const;

    QPersistentModelIndex mStartIndex;
    QPersistentModelIndex mEndIndex;
    int mStartPos = -1; // first selected character in start row
    int mEndPos = -1; // last selected character in end row
    TextAutoGenerateListViewBaseDelegate *const mDelegate;
    bool mMightStartDrag = false;
};
}
