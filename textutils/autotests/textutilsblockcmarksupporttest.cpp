/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textutilsblockcmarksupporttest.h"

#include "cmark/textutilsblockcmarksupport.h"
#include <QTest>

using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(TextUtilsBlockCMarkSupportTest)

namespace
{
// Wraps each chunk handed to addHighlighter, so the test can see which text was converted.
class MarkingBlockCMarkSupport : public TextUtils::TextUtilsBlockCMarkSupport
{
protected:
    QString addHighlighter(const QString &str,
                           [[maybe_unused]] const QString &language,
                           [[maybe_unused]] const QString &searchText,
                           [[maybe_unused]] const QByteArray &uuid,
                           [[maybe_unused]] int &blockCodeIndex,
                           [[maybe_unused]] int &numberOfTextSearched,
                           [[maybe_unused]] int hightLightStringIndex) override
    {
        return u'{' + str + u'}';
    }
};
}

TextUtilsBlockCMarkSupportTest::TextUtilsBlockCMarkSupportTest(QObject *parent)
    : QObject{parent}
{
}

void TextUtilsBlockCMarkSupportTest::shouldConvertTextAroundLinks_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("output");

    QTest::newRow("text") << u"foo"_s << u"<p>{foo}</p>\n"_s;
    QTest::newRow("link") << u"[a](http://www.kde.org)"_s << u"<p><a href=\"http://www.kde.org\">a</a></p>\n"_s;
    QTest::newRow("text-after-link") << u"[a](http://www.kde.org) foo"_s << u"<p><a href=\"http://www.kde.org\">a</a>{ foo}</p>\n"_s;
    QTest::newRow("text-between-links") << u"bla [a](http://www.kde.org) foo [b](http://www.kde.org/b) bar"_s
                                        << u"<p>{bla }<a href=\"http://www.kde.org\">a</a>{ foo }<a href=\"http://www.kde.org/b\">b</a>{ bar}</p>\n"_s;
}

void TextUtilsBlockCMarkSupportTest::shouldConvertTextAroundLinks()
{
    QFETCH(QString, input);
    QFETCH(QString, output);
    MarkingBlockCMarkSupport support;
    int numberOfTextSearched = 0;
    QCOMPARE(support.convertMessageText(input, "uuid"_ba, {}, numberOfTextSearched, -1), output);
}

#include "moc_textutilsblockcmarksupporttest.cpp"
