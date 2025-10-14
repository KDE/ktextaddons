/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textutilsblockcmarksupport.h"
#include "cmark-rc.h"
#include "textutils_cmark_debug.h"
#include <KTextToHTML>
#include <QRegularExpression>
// #define DEBUG_CMARK_RC 1
using namespace TextUtils;
using namespace Qt::StringLiterals;
TextUtilsBlockCMarkSupport::TextUtilsBlockCMarkSupport() = default;

TextUtilsBlockCMarkSupport::~TextUtilsBlockCMarkSupport() = default;

/// check if the @p str contains an uneven number of backslashes before @p pos
bool TextUtilsBlockCMarkSupport::isEscaped(const QString &str, int pos)
{
    int backslashes = 0;
    while (pos > 0 && str[pos - 1] == u'\\') {
        ++backslashes;
        --pos;
    }
    // even number of escapes means the
    return backslashes % 2 == 1;
}

int TextUtilsBlockCMarkSupport::findNonEscaped(const QString &str, const QString &regionMarker, int startFrom)
{
    while (true) {
        const int index = str.indexOf(regionMarker, startFrom);
        if (index == -1) {
            return -1;
        } else if (isEscaped(str, index)) {
            startFrom = index + regionMarker.size();
            continue;
        }
        return index;
    }
    Q_UNREACHABLE();
}

int TextUtilsBlockCMarkSupport::findNewLineOrEndLine(const QString &str, const QString &regionMarker, int startFrom)
{
    const int index = str.indexOf(regionMarker, startFrom);
    if (index == -1) {
        return str.length() - 1;
    } else {
        return index;
    }
    Q_UNREACHABLE();
}

QString TextUtilsBlockCMarkSupport::markdownToRichTextCMark(const QString &markDown)
{
    if (markDown.isEmpty()) {
        return {};
    }

    qCDebug(TEXTUTILS_CMARK_LOG) << "BEFORE markdownToRichText " << markDown;
    QString str = markDown;

    const KTextToHTML::Options convertFlags = KTextToHTML::HighlightText | KTextToHTML::ConvertPhoneNumbers;
    str = KTextToHTML::convertToHtml(str, convertFlags);
    qCDebug(TEXTUTILS_CMARK_LOG) << " AFTER convertToHtml " << str;
    // substitute "[example.com](<a href="...">...</a>)" style urls
    str = TextUtils::TextUtilsBlockCMarkSupport::convertTextWithUrl(str);
    qCDebug(TEXTUTILS_CMARK_LOG) << " AFTER convertTextWithUrl " << str;

    return str;
}

QString TextUtilsBlockCMarkSupport::convertTextWithUrl(const QString &str)
{
    static const QRegularExpression regularExpressionAHref(u"<a href=\"(.*)\">(.*)</a>"_s);
    static const QRegularExpression regularExpressionCustomAHref(u"<a href=\"(.*)\\|(.*)\">(.*)</a>"_s);
    QString newStr;
    bool isRef = false;
    bool isUrl = false;
#if 0
    bool isHasNewRef = false;
#endif
    QString url;
    QString references;
    for (int i = 0; i < str.length(); ++i) {
        const QChar ref = str.at(i);
        if (ref == u'[') {
            if (isRef) {
                isRef = false;
                newStr += u'[' + references + u'[';
                references.clear();
            } else {
                isRef = true;
            }
#if 0
        } else if (isUrl && ref == u']' && isHasNewRef) {
            isUrl = false;
            isRef = false;
            newStr += u"<a href=\'%1'>%2</a>"_s.arg(url, references);
            references.clear();
            url.clear();
#endif
        } else if (isRef && ref == u']') {
            isRef = false;
            if ((i == str.length() - 1) || (str.at(i + 1) != u'(')) {
                if (references.startsWith(u'<')) {
                    newStr += references.replace(regularExpressionCustomAHref, u"<a href=\"\\2\">\\1</a>"_s);
                } else {
                    newStr += u'[' + references + u']';
                }
                references.clear();
            }
        } else if (ref == u'(' && !references.isEmpty()) {
            isUrl = true;
        } else if (isUrl && ref == u')' && !references.isEmpty()) {
            isUrl = false;
            // detect whether the string already contains HTML <a/> tags
            if (url.startsWith(u'<')) {
                newStr += url.replace(regularExpressionAHref, u"<a href=\"\\1\">%1</a>"_s.arg(references));
            } else {
                newStr += u"<a href=\'%1'>%2</a>"_s.arg(url, references);
            }
            references.clear();
            url.clear();
#if 0
        } else if (ref == u'|' && !references.isEmpty()) {
            isUrl = true;
            isRef = false;
            isHasNewRef = true;
#endif
        } else {
            if (isRef) {
                references += ref;
            } else if (isUrl) {
                url += ref;
            } else {
                newStr += ref;
            }
        }
    }
    if (isRef) {
        newStr += u'[' + references;
    } else if (isUrl) {
        newStr += u'[' + references + "]("_L1 + url;
#if 0
    } else if (isHasNewRef) {
        if (!url.isEmpty() && !references.isEmpty()) {
            newStr += u"<a href=\'%1'>%2</a>"_s.arg(url, references);
        }
#endif
    }
    return newStr;
}

static void convertHtmlChar(QString &str)
{
    str.replace(u"&gt;"_s, u">"_s);
    str.replace(u"&lt;"_s, u"<"_s);
    str.replace(u"&quot;"_s, u"\""_s);
    str.replace(u"&amp;"_s, u"&"_s);
}

QString TextUtilsBlockCMarkSupport::convertMessageText(const QString &str,
                                                       const QByteArray &uuid,
                                                       const QString &searchText,
                                                       int &numberOfTextSearched,
                                                       int hightLightStringIndex)
{
    int blockCodeIndex = 1;
    const QByteArray ba = str.toUtf8();
    cmark_node *doc = cmark_parse_document(ba.constData(), ba.length(), CMARK_OPT_DEFAULT);
    cmark_iter *iter = cmark_iter_new(doc);
#ifdef DEBUG_CMARK_RC
    char *beforehtml = cmark_render_html(doc, CMARK_OPT_DEFAULT | CMARK_OPT_UNSAFE | CMARK_OPT_HARDBREAKS);
    qCDebug(TEXTUTILS_CMARK_LOG) << " beforehtml " << beforehtml;
    delete beforehtml;
#endif

    qCDebug(TEXTUTILS_CMARK_LOG) << " ba " << ba;

    while (cmark_iter_next(iter) != CMARK_EVENT_DONE) {
        cmark_node *node = cmark_iter_get_node(iter);
        qCDebug(TEXTUTILS_CMARK_LOG) << "type element " << cmark_node_get_type_string(node);
        switch (cmark_node_get_type(node)) {
        case CMARK_NODE_CODE_BLOCK: {
            const char *literal = cmark_node_get_literal(node);
            QString literalStr = QString::fromUtf8(literal);
            if (!literalStr.isEmpty()) {
                convertHtmlChar(literalStr);
                QString language;
                const auto l = cmark_node_get_fence_info(node);
                if (l) {
                    language = QString::fromUtf8(l);
                }
                qCDebug(TEXTUTILS_CMARK_LOG) << " language " << language;
                const QString stringHtml = u"```"_s + literalStr + u"```"_s;
                const QString highligherStr =
                    addHighlighter(stringHtml, language, searchText, uuid, blockCodeIndex, numberOfTextSearched, hightLightStringIndex);
                cmark_node *p = cmark_node_new(CMARK_NODE_PARAGRAPH);

                cmark_node *htmlInline = cmark_node_new(CMARK_NODE_HTML_INLINE);
                cmark_node_set_literal(htmlInline, highligherStr.toUtf8().constData());
                cmark_node_append_child(p, htmlInline);

                cmark_node_replace(node, p);
            }
            break;
        }
        case CMARK_NODE_TEXT: {
            const char *literal = cmark_node_get_literal(node);
            // qDebug() << " literal" << literal;
            qCDebug(TEXTUTILS_CMARK_LOG) << "CMARK_NODE_TEXT: QString::fromUtf8(literal) " << QString::fromUtf8(literal);

            const QString strLiteral = QString::fromUtf8(literal);
            if (!strLiteral.isEmpty()) {
                const QString convertedString = addHighlighter(strLiteral, {}, searchText, uuid, blockCodeIndex, numberOfTextSearched, hightLightStringIndex);
                qCDebug(TEXTUTILS_CMARK_LOG) << "CMARK_NODE_TEXT: convert text " << convertedString;
                cmark_node *htmlInline = cmark_node_new(CMARK_NODE_HTML_INLINE);
                cmark_node_set_literal(htmlInline, convertedString.toUtf8().constData());

                cmark_node_replace(node, htmlInline);
            }
            break;
        }
        case CMARK_NODE_CODE: {
            const char *literal = cmark_node_get_literal(node);
            qCDebug(TEXTUTILS_CMARK_LOG) << "CMARK_NODE_CODE:  QString::fromUtf8(literal) code" << QString::fromUtf8(literal);
            QString strLiteral = QString::fromUtf8(literal);
            if (!strLiteral.isEmpty()) {
                convertHtmlChar(strLiteral);
                const QString stringHtml = u"`"_s + strLiteral + u"`"_s;
                const QString convertedString = addHighlighter(stringHtml, {}, searchText, uuid, blockCodeIndex, numberOfTextSearched, hightLightStringIndex);
                qCDebug(TEXTUTILS_CMARK_LOG) << "CMARK_NODE_CODE:  convert text " << convertedString;
                cmark_node *htmlInline = cmark_node_new(CMARK_NODE_HTML_INLINE);
                cmark_node_set_literal(htmlInline, convertedString.toUtf8().constData());

                cmark_node_replace(node, htmlInline);
            }
            break;
        }
        default:
            break;
        }
    }

    char *html = cmark_render_html(doc, CMARK_OPT_DEFAULT | CMARK_OPT_UNSAFE | CMARK_OPT_HARDBREAKS);
    qCDebug(TEXTUTILS_CMARK_LOG) << " generated html: " << html;

    cmark_iter_free(iter);
    cmark_node_free(doc);
    const QString result = QString::fromUtf8(html);

    cmark_mem *allocator = cmark_get_default_mem_allocator();
    allocator->free(html);
    return result;
}
