/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateblockcmarksupport.h"
#include "syntaxhighlighting/textutilssyntaxhighlighter.h"
#include "textautogeneratetextcore_cmark_debug.h"
#include "widgets/view/textautogeneratecolorsandmessageviewstyle.h"
#include <KSyntaxHighlighting/Definition>
#include <KSyntaxHighlighting/Repository>
#include <KSyntaxHighlighting/Theme>
#include <KTextToHTML>
#include <QRegularExpression>
#include <TextUtils/TextUtilsSyntaxHighlightingManager>
using namespace TextAutoGenerateText;
using namespace Qt::StringLiterals;
TextAutoGenerateBlockCMarkSupport::TextAutoGenerateBlockCMarkSupport()
    : TextUtils::TextUtilsBlockCMarkSupport()
{
}

TextAutoGenerateBlockCMarkSupport::~TextAutoGenerateBlockCMarkSupport() = default;

namespace
{

/// check if the @p str contains an uneven number of backslashes before @p pos
bool isEscaped(const QString &str, int pos)
{
    int backslashes = 0;
    while (pos > 0 && str[pos - 1] == u'\\') {
        ++backslashes;
        --pos;
    }
    // even number of escapes means the
    return backslashes % 2 == 1;
}

int findNonEscaped(const QString &str, const QString &regionMarker, int startFrom)
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

QString convertTextWithUrl(const QString &str)
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

QString markdownToRichTextCMark(const QString &markDown)
{
    if (markDown.isEmpty()) {
        return {};
    }

    qCDebug(TEXTAUTOGENERATETEXT_CORE_CMARK_LOG) << "BEFORE markdownToRichText " << markDown;
    QString str = markDown;

    const KTextToHTML::Options convertFlags = KTextToHTML::HighlightText | KTextToHTML::ConvertPhoneNumbers;
    str = KTextToHTML::convertToHtml(str, convertFlags);
    qCDebug(TEXTAUTOGENERATETEXT_CORE_CMARK_LOG) << " AFTER convertToHtml " << str;
    // substitute "[example.com](<a href="...">...</a>)" style urls
    str = convertTextWithUrl(str);
    // We don't have emoji support
#if 0
    // Substiture "- [ ] foo" and "- [x] foo" to checkmark
    str = Utils::convertTextWithCheckMark(str);
#endif
    qCDebug(TEXTAUTOGENERATETEXT_CORE_CMARK_LOG) << " AFTER convertTextWithUrl " << str;

    return str;
}

QString generateRichTextCMark(const QString &str, const QString &searchedText)
{
    QString newStr = markdownToRichTextCMark(str);
    static const QRegularExpression regularExpressionAHref(u"(<a href=\'.*\'>|<a href=\".*\">)"_s);
    struct HrefPos {
        int start = 0;
        int end = 0;
    };

    if (!searchedText.isEmpty()) {
        QList<HrefPos> lstPos;
        const auto userHighlightForegroundColor =
            TextAutoGenerateColorsAndMessageViewStyle::self().schemeView().foreground(KColorScheme::NeutralText).color().name();
        const auto userHighlightBackgroundColor =
            TextAutoGenerateColorsAndMessageViewStyle::self().schemeView().background(KColorScheme::NeutralBackground).color().name();
        lstPos.clear();
        QRegularExpressionMatchIterator userIteratorHref = regularExpressionAHref.globalMatch(newStr);
        while (userIteratorHref.hasNext()) {
            const QRegularExpressionMatch match = userIteratorHref.next();
            HrefPos pos;
            pos.start = match.capturedStart(1);
            pos.end = match.capturedEnd(1);
            lstPos.append(std::move(pos));
        }

        const QRegularExpression exp(u"(%1)"_s.arg(searchedText), QRegularExpression::CaseInsensitiveOption);
        QRegularExpressionMatchIterator userIterator = exp.globalMatch(newStr);
        int offset = 0;
        while (userIterator.hasNext()) {
            const QRegularExpressionMatch match = userIterator.next();
            const QString word = match.captured(1);
            bool inAnUrl = false;
            const int matchCapturedStart = match.capturedStart(1);
            for (const HrefPos &hrefPos : lstPos) {
                if ((matchCapturedStart > hrefPos.start) && (matchCapturedStart < hrefPos.end)) {
                    inAnUrl = true;
                    break;
                }
            }
            if (inAnUrl) {
                continue;
            }
            const QString replaceStr =
                u"<a style=\"color:%2;background-color:%3;\">%1</a>"_s.arg(word, userHighlightForegroundColor, userHighlightBackgroundColor);
            newStr.replace(matchCapturedStart + offset, word.length(), replaceStr);
            // We added a new string => increase offset
            offset += replaceStr.length() - word.length();
        }
    }

    return newStr;
}

int findNewLineOrEndLine(const QString &str, const QString &regionMarker, int startFrom)
{
    const int index = str.indexOf(regionMarker, startFrom);
    if (index == -1) {
        return str.length() - 1;
    } else {
        return index;
    }
    Q_UNREACHABLE();
}
template<typename InRegionCallback, typename OutsideRegionCallback, typename NewLineCallBack>
void iterateOverEndLineRegions(const QString &str,
                               const QString &regionMarker,
                               InRegionCallback &&inRegion,
                               OutsideRegionCallback &&outsideRegion,
                               NewLineCallBack &&newLine)
{
    // We have quote text if text start with > or we have "\n>"
    if (str.startsWith(regionMarker) || str.contains(u"\n"_s + regionMarker)) {
        int startFrom = 0;
        const auto markerSize = regionMarker.size();
        bool hasCode = false;
        while (true) {
            const int startIndex = findNonEscaped(str, regionMarker, startFrom);
            if (startIndex == -1) {
                break;
            }

            const int endIndex = findNewLineOrEndLine(str, u"\n"_s, startIndex + markerSize);
            if (endIndex == -1) {
                break;
            }
            QStringView codeBlock = QStringView(str).mid(startIndex + markerSize, endIndex - startIndex).trimmed();
            if (codeBlock.endsWith(regionMarker)) {
                codeBlock.chop(regionMarker.size());
            }
            if (hasCode) {
                newLine();
            }
            const QStringView midCode = QStringView(str).mid(startFrom, startIndex - startFrom);
            outsideRegion(midCode.toString());
            startFrom = endIndex + markerSize;

            inRegion(codeBlock.toString());
            if (!codeBlock.isEmpty()) {
                hasCode = true;
            }
        }
        const QString afterstr = str.mid(startFrom);
        outsideRegion(afterstr);
    } else {
        outsideRegion(str);
    }
}

template<typename InRegionCallback, typename OutsideRegionCallback>
void iterateOverRegionsCmark(const QString &str, const QString &regionMarker, InRegionCallback &&inRegion, OutsideRegionCallback &&outsideRegion)
{
    int startFrom = 0;
    const auto markerSize = regionMarker.size();
    while (true) {
        const int startIndex = findNonEscaped(str, regionMarker, startFrom);
        if (startIndex == -1) {
            break;
        }

        const int endIndex = findNonEscaped(str, regionMarker, startIndex + markerSize);
        if (endIndex == -1) {
            break;
        }

        const int adjust = str.at(endIndex - 1) == u'\n' ? 1 : 0;
        const auto codeBlock = str.mid(startIndex + markerSize, endIndex - startIndex - markerSize - adjust);

        outsideRegion(str.mid(startFrom, startIndex - startFrom));
        startFrom = endIndex + markerSize;

        inRegion(codeBlock);
    }
    outsideRegion(str.mid(startFrom));
}
}

QString TextAutoGenerateBlockCMarkSupport::addHighlighter(const QString &str,
                                                          const QString &language,
                                                          const QString &searchText,
                                                          const QByteArray &uuid,
                                                          int &blockCodeIndex)
{
    QString richText;
    QTextStream richTextStream(&richText);
    const QColor codeBackgroundColor = TextAutoGenerateColorsAndMessageViewStyle::self().schemeView().background(KColorScheme::AlternateBackground).color();
    const auto codeBorderColor = TextAutoGenerateColorsAndMessageViewStyle::self().schemeView().foreground(KColorScheme::InactiveText).color().name();

    QString highlighted;
    QTextStream stream(&highlighted);
    TextUtils::TextUtilsSyntaxHighlighter highlighter(&stream);
    const auto useHighlighter = TextUtils::TextUtilsSyntaxHighlightingManager::self()->syntaxHighlightingInitialized();

    if (useHighlighter) {
        auto &repo = TextUtils::TextUtilsSyntaxHighlightingManager::self()->repo();
        const auto theme = (codeBackgroundColor.lightness() < 128) ? repo.defaultTheme(KSyntaxHighlighting::Repository::DarkTheme)
                                                                   : repo.defaultTheme(KSyntaxHighlighting::Repository::LightTheme);
        // qDebug() << " theme .n am" << theme.name();
        highlighter.setTheme(theme);
    }
    auto highlight = [&](const QString &codeBlock) {
        if (!useHighlighter) {
            return codeBlock;
        }
        stream.reset();
        stream.seek(0);
        highlighted.clear();
        highlighter.highlight(codeBlock, uuid, blockCodeIndex);
        return highlighted;
    };

    auto addCodeChunk = [&](const QString &chunk) {
        auto definition = TextUtils::TextUtilsSyntaxHighlightingManager::self()->def(language);
        if (!definition.isValid()) {
            definition = TextUtils::TextUtilsSyntaxHighlightingManager::self()->defaultDef();
        }
        qCDebug(TEXTAUTOGENERATETEXT_CORE_CMARK_LOG) << " definition.name() " << definition.name();
        highlighter.setDefinition(definition);
        // Qt's support for borders is limited to tables, so we have to jump through some hoops...
        richTextStream << "<table><tr><td style='background-color:"_L1 << codeBackgroundColor.name() << "; padding: 5px; border: 1px solid "_L1
                       << codeBorderColor << "'>"_L1 << highlight(chunk) << "</td></tr></table>"_L1;
    };

    auto addInlineCodeChunk = [&](const QString &chunk) {
        richTextStream << "<code style='background-color:"_L1 << codeBackgroundColor.name() << "'>"_L1 << chunk.toHtmlEscaped() << "</code>"_L1;
    };

    auto addTextChunk = [&](const QString &chunk) {
        auto htmlChunk = generateRichTextCMark(chunk, searchText);
        richTextStream << htmlChunk;
    };
    auto addInlineQuoteCodeChunk = [&](const QString &chunk) {
        auto htmlChunk = generateRichTextCMark(chunk, searchText);
        richTextStream << "<code style='background-color:"_L1 << codeBackgroundColor.name() << "'>"_L1 << htmlChunk << "</code>"_L1;
    };

    auto addInlineQuoteCodeNewLineChunk = [&]() {
        richTextStream << "<br />"_L1;
    };

    auto addInlineQuoteChunk = [&](const QString &chunk) {
        iterateOverEndLineRegions(chunk, u">"_s, addInlineQuoteCodeChunk, addTextChunk, addInlineQuoteCodeNewLineChunk);
    };
    auto addNonCodeChunk = [&](const QString &chunk) {
        if (chunk.isEmpty()) {
            return;
        }
        iterateOverRegionsCmark(chunk, u"`"_s, addInlineCodeChunk, addInlineQuoteChunk);
    };

    iterateOverRegionsCmark(str, u"```"_s, addCodeChunk, addNonCodeChunk);

    qCDebug(TEXTAUTOGENERATETEXT_CORE_CMARK_LOG) << " richText generated: " << richText;
    return richText;
}
// #define DEBUG_CMARK_RC
