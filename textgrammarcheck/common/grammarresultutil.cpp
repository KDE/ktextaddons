/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammarresultutil.h"
#include "textgrammarcheck_debug.h"

#include <KLocalizedString>
#include <QTextBlock>
#include <QTextDocument>
using namespace TextGrammarCheck;

void GrammarResultUtil::applyGrammarResult(const QVector<TextGrammarCheck::GrammarError> &infos, QTextDocument *document, const QColor &negativeTextColor)
{
    for (const TextGrammarCheck::GrammarError &info : infos) {
        int blockNumberId = info.blockId();
        int startSelectionIndex = info.start();
        // Block id based on 1 not 0 as QTextDocument (perhaps remove -1 when loading ?)
        if (blockNumberId == -1) { // Languagetool adapt grammar error We need to generate info. By default languagetool uses 1 paragraph info.
            const QTextBlock firstBlock = document->findBlockByNumber(0);
            if (firstBlock.isValid()) {
                QTextCursor cur(document);

                cur.setPosition(info.start());
                blockNumberId = cur.blockNumber();
                for (int i = 0; i < blockNumberId; ++i) {
                    const QTextBlock block = document->findBlockByNumber(i);
                    if (block.isValid()) {
                        if (block.text() != u'\n') {
                            startSelectionIndex -= block.length();
                        }
                    }
                }
            }
        } else {
            blockNumberId = info.blockId() - 1;
        }
        QTextBlock block = document->findBlockByNumber(blockNumberId);
        if (block.isValid()) {
            QTextCursor cur(block);
            QTextCharFormat format;
            // Verify color
            format.setBackground(info.color().isValid() ? info.color() : negativeTextColor);
            QString toolTip = info.error();
            // TODO generate new tooltip!
            if (!info.url().isEmpty()) {
                toolTip += u'\n' + i18n("See on: %1", info.url());
            }
            format.setToolTip(toolTip);
            TextGrammarCheck::GrammarAction act;
            act.setLength(info.length());
            act.setStart(startSelectionIndex);
            act.setSuggestions(info.suggestions());
            act.setBlockId(blockNumberId + 1);
            if (!info.url().isEmpty()) {
                act.setInfoUrls({info.url()});
            }
            format.setProperty(ReplaceFormatInfo, QVariant::fromValue(act));
            const int position = cur.position() + startSelectionIndex;
            cur.setPosition(position);
            cur.setPosition(position + info.length(), QTextCursor::KeepAnchor);
            cur.mergeCharFormat(format);
        } else {
            qCWarning(TEXTGRAMMARCHECK_LOG) << "Unable to find block Id" << (info.blockId() - 1);
        }
    }
}

void GrammarResultUtil::replaceWord(const TextGrammarCheck::GrammarAction &act, const QString &replacementWord, QTextDocument *document)
{
    QTextBlock block = document->findBlockByNumber(act.blockId() - 1);
    if (block.isValid()) {
        QTextCursor cur(block);
        const int initialCurrentPosition = cur.position();
        qCDebug(TEXTGRAMMARCHECK_LOG) << " cur.position()" << cur.position();
        const int position = cur.position() + act.start();
        cur.setPosition(position);
        cur.setPosition(position + act.length(), QTextCursor::KeepAnchor);
        QTextCharFormat format;
        cur.insertText(replacementWord, format);
        const int diff = replacementWord.length() - act.length();
        qCDebug(TEXTGRAMMARCHECK_LOG) << " diff " << diff;
        if (diff != 0) {
            const int blockLength = block.length();
            qCDebug(TEXTGRAMMARCHECK_LOG) << "current blockLength " << blockLength << " position " << position << "";
            for (int i = position + replacementWord.length() + 1; i < blockLength + initialCurrentPosition; ++i) {
                cur.setPosition(i);
                qCDebug(TEXTGRAMMARCHECK_LOG) << " Position  " << i;
                QTextCharFormat currentCharFormat = cur.charFormat();
                if (currentCharFormat.hasProperty(GrammarResultUtil::TextInfo::ReplaceFormatInfo)) {
                    auto grammarAct = cur.charFormat().property(GrammarResultUtil::TextInfo::ReplaceFormatInfo).value<TextGrammarCheck::GrammarAction>();
                    qCDebug(TEXTGRAMMARCHECK_LOG) << "BEFORE Update GrammarResultUtil::TextInfo::ReplaceFormatInfo " << grammarAct;
                    grammarAct.setStart(grammarAct.start() + diff);
                    qCDebug(TEXTGRAMMARCHECK_LOG) << "AFTER Update GrammarResultUtil::TextInfo::ReplaceFormatInfo " << grammarAct.start();
                    currentCharFormat.setProperty(GrammarResultUtil::TextInfo::ReplaceFormatInfo, QVariant::fromValue(grammarAct));

                    const int newPosition = i - 1;
                    qCDebug(TEXTGRAMMARCHECK_LOG) << " newPosition " << newPosition;
                    qCDebug(TEXTGRAMMARCHECK_LOG) << "BEFORE Update GrammarResultUtil::TextInfo::ReplaceFormatInfo newPosition " << newPosition;
                    cur.setPosition(newPosition);
                    cur.setPosition(newPosition + grammarAct.length(), QTextCursor::KeepAnchor);
                    qCDebug(TEXTGRAMMARCHECK_LOG) << "AFTER Update GrammarResultUtil::TextInfo::ReplaceFormatInfo newPosition "
                                                  << newPosition + grammarAct.length();
                    cur.setCharFormat(currentCharFormat);

                    i += grammarAct.length();
                }
            }
        }
    }
}
