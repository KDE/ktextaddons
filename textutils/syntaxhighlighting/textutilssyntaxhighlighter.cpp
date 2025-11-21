/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textutilssyntaxhighlighter.h"
#include "textutilsblockcodemanager.h"
#include "textutilsiconnamecache.h"

#include <KSyntaxHighlighting/Format>
#include <KSyntaxHighlighting/State>
#include <KSyntaxHighlighting/Theme>

#include <KIconLoader>
#include <KLocalizedString>
#include <QTextStream>
using namespace TextUtils;
using namespace Qt::Literals::StringLiterals;
TextUtilsSyntaxHighlighter::TextUtilsSyntaxHighlighter(QTextStream *stream)
    : mStream(stream)
{
}

void TextUtilsSyntaxHighlighter::highlight(const QString &str, const QByteArray &uuid, int &blockCodeIndex)
{
    *mStream << u"<code>"_s;
    KSyntaxHighlighting::State state;

    int lineStart = 0;
    int lineEnd = str.indexOf(u'\n');

    const bool addIcon = !uuid.isEmpty();
    if (addIcon) {
        *mStream << u"<table border=\"0\" cellspacing=\"0\" cellpadding=\"0\"><tr><td>"_s;
    }
    for (; lineEnd != -1; lineStart = lineEnd + 1, lineEnd = str.indexOf(u'\n', lineStart)) {
        mCurrentLine = str.mid(lineStart, lineEnd - lineStart);
        state = highlightLine(mCurrentLine, state);
        *mStream << u"<br>"_s;
    }
    if (lineStart < str.size()) { // remaining content if str isn't ending with a newline
        mCurrentLine = str.mid(lineStart);
        state = highlightLine(mCurrentLine, state);
    }

    if (addIcon) {
        const int iconSize = KIconLoader::global()->currentSize(KIconLoader::Small);
        // TODO fix use custom palette => get palette here
        const QString copyIconPath = TextUtilsIconNameCache::self()->iconPath(u"edit-copy"_s, KIconLoader::Small);

        const QString identifier = QString(QString::fromLatin1(uuid) + u'-' + QString::number(blockCodeIndex++));

        TextUtilsBlockCodeManager::self()->insert(identifier, str);

        *mStream << u"</td><td align=\"right\" valign=\"top\">"_s;

        // Add copy url
        *mStream << u"<a href=\"%4%1\"><img height=\"%2\" width=\"%2\" src=\"%3\"></a></div>"_s.arg(identifier,
                                                                                                    QString::number(iconSize),
                                                                                                    copyIconPath,
                                                                                                    copyHref());
        *mStream << u"</td></tr></table>"_s;
    }
    *mStream << "</code>"_L1;
}

QString TextUtilsSyntaxHighlighter::copyHref()
{
    return u"copy:/"_s;
}

void TextUtilsSyntaxHighlighter::applyFormat(int offset, int length, const KSyntaxHighlighting::Format &format)
{
    const bool isDefaultTextStyle = format.isDefaultTextStyle(theme());
    if (!isDefaultTextStyle) {
        *mStream << u"<span style=\""_s;
        if (format.hasTextColor(theme())) {
            *mStream << u"color:"_s << format.textColor(theme()).name() << u";"_s;
        }
        if (format.hasBackgroundColor(theme())) {
            *mStream << u"background-color:"_s << format.backgroundColor(theme()).name() << u";"_s;
        }
        if (format.isBold(theme())) {
            *mStream << u"font-weight:bold;"_s;
        }
        if (format.isItalic(theme())) {
            *mStream << u"font-style:italic;"_s;
        }
        if (format.isUnderline(theme())) {
            *mStream << u"text-decoration:underline;"_s;
        }
        if (format.isStrikeThrough(theme())) {
            *mStream << u"text-decoration:line-through;"_s;
        }
        *mStream << u"\">"_s;
    }
    QString str = mCurrentLine.mid(offset, length).toHtmlEscaped();
    str = str.replace(u'\t', "    "_L1);
    str = str.replace(u' ', "&nbsp;"_L1);
    *mStream << str;

    if (!isDefaultTextStyle) {
        *mStream << u"</span>"_s;
    }
}
