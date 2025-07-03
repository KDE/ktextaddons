/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratemessageutils.h"
#include <KSyntaxHighlighting/Definition>
#include <KSyntaxHighlighting/Repository>
#include <KSyntaxHighlighting/Theme>
#include <KTextToHTML>

// TODO add syntax higthlighting
QString TextAutoGenerateText::TextAutoGenerateMessageUtils::convertTextToHtml(const QString &str)
{
    const KTextToHTML::Options convertFlags = KTextToHTML::HighlightText | KTextToHTML::ConvertPhoneNumbers;
    return KTextToHTML::convertToHtml(str, convertFlags);
}

#if 0
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
static QString addHighlighter(const QString &str, const TextConverter::ConvertMessageTextSettings &settings)
{
    QString richText;
    QTextStream richTextStream(&richText);
    const QColor codeBackgroundColor = ColorsAndMessageViewStyle::self().schemeView().background(KColorScheme::AlternateBackground).color();
    const auto codeBorderColor = ColorsAndMessageViewStyle::self().schemeView().foreground(KColorScheme::InactiveText).color().name();

    QString highlighted;
    QTextStream stream(&highlighted);
    TextHighlighter highlighter(&stream);
    const auto useHighlighter = SyntaxHighlightingManager::self()->syntaxHighlightingInitialized();

    if (useHighlighter) {
        auto &repo = SyntaxHighlightingManager::self()->repo();
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
        highlighter.highlight(codeBlock);
        return highlighted;
    };

    auto addCodeChunk = [&](QString chunk) {
        const auto language = [&]() {
            const auto newline = chunk.indexOf(u'\n');
            if (newline == -1) {
                return QString();
            }
            return chunk.left(newline);
        }();

        auto definition = SyntaxHighlightingManager::self()->def(language);
        if (definition.isValid()) {
            chunk.remove(0, language.size() + 1);
        } else {
            definition = SyntaxHighlightingManager::self()->defaultDef();
        }

        highlighter.setDefinition(std::move(definition));
        // Qt's support for borders is limited to tables, so we have to jump through some hoops...
        richTextStream << "<table><tr><td style='background-color:"_L1 << codeBackgroundColor.name() << "; padding: 5px; border: 1px solid "_L1
                       << codeBorderColor << "'>"_L1 << highlight(chunk) << "</td></tr></table>"_L1;
    };

    auto addInlineCodeChunk = [&](const QString &chunk) {
        richTextStream << "<code style='background-color:"_L1 << codeBackgroundColor.name() << "'>"_L1 << chunk.toHtmlEscaped() << "</code>"_L1;
    };

    auto addTextChunk = [&](const QString &chunk) {
        auto htmlChunk = generateRichTextCMark(chunk, settings.userName, settings.highlightWords, settings.mentions, settings.channels, settings.searchedText);
        if (settings.emojiManager) {
            settings.emojiManager->replaceEmojis(&htmlChunk);
        }
        richTextStream << htmlChunk;
    };
    auto addInlineQuoteCodeChunk = [&](const QString &chunk) {
        auto htmlChunk = generateRichTextCMark(chunk, settings.userName, settings.highlightWords, settings.mentions, settings.channels, settings.searchedText);
        if (settings.emojiManager) {
            settings.emojiManager->replaceEmojis(&htmlChunk);
        }
        richTextStream << "<code style='background-color:"_L1 << codeBackgroundColor.name() << "'>"_L1 << htmlChunk << "</code>"_L1;
    };

    auto addInlineQuoteCodeNewLineChunk = [&]() {
        richTextStream << "<br />"_L1;
    };

    auto addInlineQuoteChunk = [&](const QString &chunk) {
        iterateOverEndLineRegions(chunk, u">"_s, addInlineQuoteCodeChunk, addTextChunk, addInlineQuoteCodeNewLineChunk);
    };
    auto addNonCodeChunk = [&](QString chunk) {
        if (chunk.isEmpty()) {
            return;
        }

        iterateOverRegionsCmark(chunk, u"`"_s, addInlineCodeChunk, addInlineQuoteChunk);
    };

    iterateOverRegionsCmark(str, u"```"_s, addCodeChunk, addNonCodeChunk);

    qCDebug(RUQOLA_TEXTTOHTML_CMARK_LOG) << " richText generated: " << richText;
    return richText;
}

// #define DEBUG_CMARK_RC

static void convertHtmlChar(QString &str)
{
    str.replace(u"&gt;"_s, u">"_s);
    str.replace(u"&lt;"_s, u"<"_s);
    str.replace(u"&quot;"_s, u"\""_s);
    str.replace(u"&amp;"_s, u"&"_s);
}


static QString convertMessageText(const TextConverter::ConvertMessageTextSettings &newSettings, const QString &quotedMessage)
{
    // Need to escaped text (avoid to interpret html code)
    const TextConverter::ConvertMessageTextSettings settings{
        quotedMessage + newSettings.str.toHtmlEscaped(),
        newSettings.userName,
        newSettings.allMessages,
        newSettings.highlightWords,
        newSettings.emojiManager,
        newSettings.messageCache,
        newSettings.mentions,
        newSettings.channels,
        newSettings.searchedText,
        newSettings.maximumRecursiveQuotedText,
    };
    const QByteArray ba = settings.str.toUtf8();
    cmark_node *doc = cmark_parse_document(ba.constData(), ba.length(), CMARK_OPT_DEFAULT);
    cmark_iter *iter = cmark_iter_new(doc);
#ifdef DEBUG_CMARK_RC
    qCDebug(RUQOLA_TEXTTOHTML_CMARK_LOG) << " quotedMessage + newSettings.str.toHtmlEscaped() " << quotedMessage + newSettings.str.toHtmlEscaped();
    char *beforehtml = cmark_render_html(doc, CMARK_OPT_DEFAULT | CMARK_OPT_UNSAFE | CMARK_OPT_HARDBREAKS);
    qCDebug(RUQOLA_TEXTTOHTML_CMARK_LOG) << " beforehtml " << beforehtml;
    delete beforehtml;
#endif

    qCDebug(RUQOLA_TEXTTOHTML_CMARK_LOG) << " ba " << ba;

    while (cmark_iter_next(iter) != CMARK_EVENT_DONE) {
        cmark_node *node = cmark_iter_get_node(iter);
        qCDebug(RUQOLA_TEXTTOHTML_CMARK_LOG) << "type element " << cmark_node_get_type_string(node);
        switch (cmark_node_get_type(node)) {
        case CMARK_NODE_CODE_BLOCK: {
            const char *literal = cmark_node_get_literal(node);
            QString str = QString::fromUtf8(literal);
            if (!str.isEmpty()) {
                convertHtmlChar(str);
                const QString stringHtml = u"```"_s + str + u"```"_s;
                // qDebug() << " stringHtml " << stringHtml;
                const QString highligherStr = addHighlighter(stringHtml, settings);
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
            qCDebug(RUQOLA_TEXTTOHTML_CMARK_LOG) << "CMARK_NODE_TEXT: QString::fromUtf8(literal) " << QString::fromUtf8(literal);

            const QString str = QString::fromUtf8(literal);
            if (!str.isEmpty()) {
                const QString convertedString = addHighlighter(str, settings);
                qCDebug(RUQOLA_TEXTTOHTML_CMARK_LOG) << "CMARK_NODE_TEXT: convert text " << convertedString;
                cmark_node *htmlInline = cmark_node_new(CMARK_NODE_HTML_INLINE);
                cmark_node_set_literal(htmlInline, convertedString.toUtf8().constData());

                cmark_node_replace(node, htmlInline);
            }
            break;
        }
        case CMARK_NODE_CODE: {
            const char *literal = cmark_node_get_literal(node);
            qCDebug(RUQOLA_TEXTTOHTML_CMARK_LOG) << "CMARK_NODE_CODE:  QString::fromUtf8(literal) code" << QString::fromUtf8(literal);
            QString str = QString::fromUtf8(literal);
            if (!str.isEmpty()) {
                convertHtmlChar(str);
                const QString stringHtml = u"`"_s + str + u"`"_s;
                const QString convertedString = addHighlighter(stringHtml, settings);
                qCDebug(RUQOLA_TEXTTOHTML_CMARK_LOG) << "CMARK_NODE_CODE:  convert text " << convertedString;
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
    qCDebug(RUQOLA_TEXTTOHTML_CMARK_LOG) << " generated html: " << html;

    cmark_iter_free(iter);
    cmark_node_free(doc);
    QString result = QString::fromUtf8(html);

    cmark_mem *allocator = cmark_get_default_mem_allocator();
    allocator->free(html);

    return result;
}

#endif
