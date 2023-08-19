/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "converttext.h"
#include <QChar>
#include <QString>

using namespace TextUtils;

// code from kitinerary/src/lib/stringutil.cpp
QString ConvertText::normalize(QStringView str)
{
    QString out;
    out.reserve(str.size());
    for (const auto c : str) {
        // case folding
        const auto n = c.toCaseFolded();

        // if the character has a canonical decomposition use that and skip the
        // combining diacritic markers following it
        // see https://en.wikipedia.org/wiki/Unicode_equivalence
        // see https://en.wikipedia.org/wiki/Combining_character
        if (n.decompositionTag() == QChar::Canonical) {
            out.push_back(n.decomposition().at(0));
        }
        // handle compatibility compositions such as ligatures
        // see https://en.wikipedia.org/wiki/Unicode_compatibility_characters
        else if (n.decompositionTag() == QChar::Compat && n.isLetter() && n.script() == QChar::Script_Latin) {
            out.append(n.decomposition());
        } else {
            out.push_back(n);
        }
    }
    return out;
}

void ConvertText::upperCase(QTextCursor &cursor)
{
    if (cursor.hasSelection()) {
        const QString newText = cursor.selectedText().toUpper();
        cursor.insertText(newText);
    }
}

void ConvertText::lowerCase(QTextCursor &cursor)
{
    if (cursor.hasSelection()) {
        const QString newText = cursor.selectedText().toLower();
        cursor.insertText(newText);
    }
}

void ConvertText::sentenceCase(QTextCursor &cursor)
{
    if (cursor.hasSelection()) {
        QString newText = cursor.selectedText();
        const int nbChar(newText.length());
        for (int i = 0; i < nbChar; ++i) {
            if (i == 0 && newText.at(0).isLetter()) {
                newText.replace(0, 1, newText.at(0).toUpper());
            } else if (newText.at(i) == QChar::ParagraphSeparator || newText.at(i) == QChar::LineSeparator) {
                ++i;
                if (i < nbChar) {
                    if (newText.at(i).isLetter()) {
                        newText.replace(i, 1, newText.at(i).toUpper());
                    }
                }
            }
        }
        cursor.insertText(newText);
    }
}

void ConvertText::reverseCase(QTextCursor &cursor)
{
    if (cursor.hasSelection()) {
        const QString newText = cursor.selectedText();
        QString reverseCaseText;
        const int nbChar(newText.length());
        for (int i = 0; i < nbChar; ++i) {
            QChar charVal = newText.at(i);
            if (charVal.isLetter()) {
                if (charVal.isLower()) {
                    charVal = charVal.toUpper();
                } else {
                    charVal = charVal.toLower();
                }
            }
            reverseCaseText += charVal;
        }
        cursor.insertText(reverseCaseText);
    }
}
