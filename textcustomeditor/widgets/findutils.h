/*
   SPDX-FileCopyrightText: 2020 Igor Poboiko <igor.poboiko@gmail.com>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textcustomeditor_private_export.h"
#include <QChar>
#include <QTextDocument>
#include <TextCustomEditor/TextEditFindBarBase>
#include <qglobal.h>
class QPlainTextEdit;
class QTextEdit;
namespace TextCustomEditor
{

namespace FindUtils
{
/**
 * Replaces all occurrences of a search string provided by @p findWidget
 * by a string provided by @p replaceWidget in a @p document
 *
 * @return number of replacements done
 */
[[nodiscard]] TEXTCUSTOMEDITOR_TESTS_EXPORT int
replaceAll(QPlainTextEdit *view, const QString &str, const QString &replaceWidget, TextEditFindBarBase::FindFlags searchOptions);
[[nodiscard]] TEXTCUSTOMEDITOR_TESTS_EXPORT int
replaceAll(QTextEdit *view, const QString &str, const QString &replaceWidget, TextEditFindBarBase::FindFlags searchOptions);
[[nodiscard]] TEXTCUSTOMEDITOR_TESTS_EXPORT int
replaceAll(QTextDocument *document, const QRegularExpression &regExp, const QString &replaceWidget, TextEditFindBarBase::FindFlags searchOptions);
[[nodiscard]] bool find(QPlainTextEdit *view, const QString &searchText, QTextDocument::FindFlags searchOptions);
[[nodiscard]] bool find(QTextEdit *view, const QString &searchText, QTextDocument::FindFlags searchOptions);
[[nodiscard]] QTextDocument::FindFlags convertTextEditFindFlags(TextEditFindBarBase::FindFlags textEditFlags);
}
} // namespace TextCustomEditor
