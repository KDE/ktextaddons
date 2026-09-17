/*
   SPDX-FileCopyrightText: 2020 Igor Poboiko <igor.poboiko@gmail.com>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "findutils.h"
#include <TextUtils/ConvertText>

#include <QPlainTextEdit>
#include <QRegularExpression>
#include <QTextCursor>
#include <QTextEdit>

#include <algorithm>
#include <utility>

using namespace TextCustomEditor;

namespace
{
[[nodiscard]] Qt::CaseSensitivity caseSensitivityOf(QTextDocument::FindFlags flags)
{
    return (flags & QTextDocument::FindCaseSensitively) ? Qt::CaseSensitive : Qt::CaseInsensitive;
}

// Searching happens on a normalized copy of the text and normalize() is not length preserving, as a Latin
// ligature expands to several characters. This maps a [start, end) range of the copy back to the original
// text. A match may start or end inside an expanded character, in which case that whole character is
// taken: half a ligature cannot be selected, let alone replaced.
[[nodiscard]] std::pair<int, int> sourceRange(const QList<qsizetype> &sourcePositions, int start, int end)
{
    const int sourceStart = static_cast<int>(sourcePositions.at(start));
    int sourceEnd = static_cast<int>(sourcePositions.at(end));
    if (sourceEnd <= sourceStart && end > start) {
        sourceEnd = static_cast<int>(sourcePositions.at(end - 1)) + 1;
    }
    return {sourceStart, sourceEnd};
}

// Inverse mapping: the first position of the normalized copy that comes from sourcePosition or later.
[[nodiscard]] int normalizedPosition(const QList<qsizetype> &sourcePositions, int sourcePosition)
{
    const auto it = std::lower_bound(sourcePositions.cbegin(), sourcePositions.cend(), static_cast<qsizetype>(sourcePosition));
    return static_cast<int>(std::distance(sourcePositions.cbegin(), it));
}
}
QTextDocument::FindFlags FindUtils::convertTextEditFindFlags(TextEditFindBarBase::FindFlags textEditFlags)
{
    QTextDocument::FindFlags flags;
    if (textEditFlags & TextEditFindBarBase::FindBackward) {
        flags |= QTextDocument::FindBackward;
    }
    if (textEditFlags & TextEditFindBarBase::FindCaseSensitively) {
        flags |= QTextDocument::FindCaseSensitively;
    }
    if (textEditFlags & TextEditFindBarBase::FindWholeWords) {
        flags |= QTextDocument::FindWholeWords;
    }
    return flags;
}

int FindUtils::replaceAll(QTextEdit *view, const QString &str, const QString &replaceStr, TextEditFindBarBase::FindFlags searchOptions)
{
    auto document = view->document();
    int count = 0;
    // Ignoring FindBackward when replacing all
    const QTextDocument::FindFlags flags = FindUtils::convertTextEditFindFlags(searchOptions) & ~QTextDocument::FindBackward;
    if (searchOptions & TextEditFindBarBase::FindFlag::FindRespectDiacritics) {
        QTextCursor c(document);
        c.beginEditBlock();
        while (!c.isNull()) {
            c = document->find(str, c, flags);
            if (!c.isNull()) {
                c.insertText(replaceStr);
                count++;
            } else {
                break;
            }
        }
        c.endEditBlock();
    } else {
        // normalize() folds the case, so keep it when the search is case sensitive.
        const Qt::CaseSensitivity caseSensitivity = caseSensitivityOf(flags);
        QList<qsizetype> sourcePositions;
        const QString normalizedText{TextUtils::ConvertText::normalize(view->toPlainText(), caseSensitivity, &sourcePositions)};
        const QString normalizedSearchStr{TextUtils::ConvertText::normalize(str, caseSensitivity)};
        if (normalizedSearchStr.isEmpty()) {
            return 0;
        }

        // Collect every match before touching the document: the positions come from the normalized copy and
        // have to be mapped back, so replacing as we go would invalidate that mapping.
        QList<std::pair<int, int>> ranges;
        QTextDocument normalizedDocument(normalizedText);
        QTextCursor normalizedCursor(&normalizedDocument);
        while (true) {
            normalizedCursor = normalizedDocument.find(normalizedSearchStr, normalizedCursor, flags);
            if (normalizedCursor.isNull()) {
                break;
            }
            ranges.append(sourceRange(sourcePositions, normalizedCursor.selectionStart(), normalizedCursor.selectionEnd()));
        }

        // Replace backwards so that the positions of the matches left to do stay valid.
        QTextCursor c(document);
        c.beginEditBlock();
        for (auto it = ranges.crbegin(), endIt = ranges.crend(); it != endIt; ++it) {
            c.setPosition(it->first);
            c.setPosition(it->second, QTextCursor::KeepAnchor);
            c.insertText(replaceStr);
        }
        c.endEditBlock();
        count = static_cast<int>(ranges.size());
    }
    return count;
}

int FindUtils::replaceAll(QPlainTextEdit *view, const QString &str, const QString &replaceStr, TextEditFindBarBase::FindFlags searchOptions)
{
    auto document = view->document();
    int count = 0;
    // Ignoring FindBackward when replacing all
    const QTextDocument::FindFlags flags = FindUtils::convertTextEditFindFlags(searchOptions) & ~QTextDocument::FindBackward;
    if (searchOptions & TextEditFindBarBase::FindFlag::FindRespectDiacritics) {
        QTextCursor c(document);
        c.beginEditBlock();
        while (!c.isNull()) {
            c = document->find(str, c, flags);
            if (!c.isNull()) {
                c.insertText(replaceStr);
                count++;
            } else {
                break;
            }
        }
        c.endEditBlock();
    } else {
        // normalize() folds the case, so keep it when the search is case sensitive.
        const Qt::CaseSensitivity caseSensitivity = caseSensitivityOf(flags);
        QList<qsizetype> sourcePositions;
        const QString normalizedText{TextUtils::ConvertText::normalize(view->toPlainText(), caseSensitivity, &sourcePositions)};
        const QString normalizedSearchStr{TextUtils::ConvertText::normalize(str, caseSensitivity)};
        if (normalizedSearchStr.isEmpty()) {
            return 0;
        }

        // Collect every match before touching the document: the positions come from the normalized copy and
        // have to be mapped back, so replacing as we go would invalidate that mapping.
        QList<std::pair<int, int>> ranges;
        QTextDocument normalizedDocument(normalizedText);
        QTextCursor normalizedCursor(&normalizedDocument);
        while (true) {
            normalizedCursor = normalizedDocument.find(normalizedSearchStr, normalizedCursor, flags);
            if (normalizedCursor.isNull()) {
                break;
            }
            ranges.append(sourceRange(sourcePositions, normalizedCursor.selectionStart(), normalizedCursor.selectionEnd()));
        }

        // Replace backwards so that the positions of the matches left to do stay valid.
        QTextCursor c(document);
        c.beginEditBlock();
        for (auto it = ranges.crbegin(), endIt = ranges.crend(); it != endIt; ++it) {
            c.setPosition(it->first);
            c.setPosition(it->second, QTextCursor::KeepAnchor);
            c.insertText(replaceStr);
        }
        c.endEditBlock();
        count = static_cast<int>(ranges.size());
    }
    return count;
}

int FindUtils::replaceAll(QTextDocument *document, const QRegularExpression &regExp, const QString &replaceWidget, TextEditFindBarBase::FindFlags searchOptions)
{
    QTextCursor c(document);
    c.beginEditBlock();
    int count = 0;
    // Ignoring FindBackward when replacing all
    const QTextDocument::FindFlags flags = FindUtils::convertTextEditFindFlags(searchOptions) & ~QTextDocument::FindBackward;
    while (!c.isNull()) {
        c = document->find(regExp, c, flags);
        if (!c.isNull()) {
            // find() selects found text, and insertText() replaces selection
            c.insertText(replaceWidget);
            count++;
        } else {
            break;
        }
    }
    c.endEditBlock();
    return count;
}

bool FindUtils::find(QPlainTextEdit *view, const QString &searchText, QTextDocument::FindFlags searchOptions)
{
    // normalize() folds the case, so keep it when the caller asked for a case sensitive search,
    // otherwise QTextDocument::FindCaseSensitively below has nothing left to discriminate.
    const Qt::CaseSensitivity caseSensitivity = caseSensitivityOf(searchOptions);
    QList<qsizetype> sourcePositions;
    const QString text = TextUtils::ConvertText::normalize(view->document()->toPlainText(), caseSensitivity, &sourcePositions);
    QTextDocument doc(text);
    QTextCursor c(&doc);
    QTextCursor docCusor(view->textCursor());
    c.setPosition(normalizedPosition(sourcePositions, docCusor.position()));
    c = doc.find(TextUtils::ConvertText::normalize(searchText, caseSensitivity), c, searchOptions);
    if (!c.isNull()) {
        const auto [selectionStart, selectionEnd] = sourceRange(sourcePositions, c.selectionStart(), c.selectionEnd());
        if (searchOptions & QTextDocument::FindBackward) {
            docCusor.setPosition(selectionEnd);
            docCusor.setPosition(selectionStart, QTextCursor::KeepAnchor);
        } else {
            docCusor.setPosition(selectionStart);
            docCusor.setPosition(selectionEnd, QTextCursor::KeepAnchor);
        }
        view->setTextCursor(docCusor);
        view->ensureCursorVisible();
        return true;
    }
    return false;
}

bool FindUtils::find(QTextEdit *view, const QString &searchText, QTextDocument::FindFlags searchOptions)
{
    // normalize() folds the case, so keep it when the caller asked for a case sensitive search,
    // otherwise QTextDocument::FindCaseSensitively below has nothing left to discriminate.
    const Qt::CaseSensitivity caseSensitivity = caseSensitivityOf(searchOptions);
    QList<qsizetype> sourcePositions;
    const QString text = TextUtils::ConvertText::normalize(view->document()->toPlainText(), caseSensitivity, &sourcePositions);
    QTextDocument doc(text);
    QTextCursor c(&doc);
    QTextCursor docCusor(view->textCursor());
    c.setPosition(normalizedPosition(sourcePositions, docCusor.position()));
    c = doc.find(TextUtils::ConvertText::normalize(searchText, caseSensitivity), c, searchOptions);
    if (!c.isNull()) {
        const auto [selectionStart, selectionEnd] = sourceRange(sourcePositions, c.selectionStart(), c.selectionEnd());
        if (searchOptions & QTextDocument::FindBackward) {
            docCusor.setPosition(selectionEnd);
            docCusor.setPosition(selectionStart, QTextCursor::KeepAnchor);
        } else {
            docCusor.setPosition(selectionStart);
            docCusor.setPosition(selectionEnd, QTextCursor::KeepAnchor);
        }
        view->setTextCursor(docCusor);
        view->ensureCursorVisible();
        return true;
    }
    return false;
}
