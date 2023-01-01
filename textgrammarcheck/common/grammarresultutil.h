/*
   SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "grammaraction.h"
#include "grammarerror.h"
#include "textgrammarcheck_export.h"

#include <QTextFormat>
namespace TextGrammarCheck
{
namespace GrammarResultUtil
{
enum TextInfo {
    ReplaceFormatInfo = QTextFormat::UserProperty + 1,
};
TEXTGRAMMARCHECK_EXPORT void applyGrammarResult(const QVector<TextGrammarCheck::GrammarError> &infos, QTextDocument *document, const QColor &negativeTextColor);
TEXTGRAMMARCHECK_EXPORT void replaceWord(const TextGrammarCheck::GrammarAction &act, const QString &replacementWord, QTextDocument *document);
}
}
