/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "richtextquicktextformattest.h"
#include "richtextquicktextformat.h"
#include <QHBoxLayout>
#include <QSignalSpy>
#include <QTest>
#include <QToolButton>
#include <qtestmouse.h>
QTEST_MAIN(RichTextQuickTextFormatTest)
using namespace Qt::Literals::StringLiterals;
RichTextQuickTextFormatTest::RichTextQuickTextFormatTest(QObject *parent)
    : QObject{parent}
{
}

void RichTextQuickTextFormatTest::shouldHaveDefaultValues()
{
    TextAddonsWidgets::RichTextQuickTextFormat t(nullptr);
    QCOMPARE(t.focusPolicy(), Qt::NoFocus);

    QCOMPARE(t.formatTypes(),
             TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatTypes{TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::Unknown});

    TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatTypes formatTypes = TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::Unknown;
    formatTypes |= TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::Bold;
    formatTypes |= TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::Italic;
    formatTypes |= TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::StrikeThrough;
    formatTypes |= TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::BlockQuote;
    formatTypes |= TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::InsertLink;
    formatTypes |= TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::CodeBlock;
    formatTypes |= TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::UnderLine;
    t.setFormatTypes(formatTypes);

    auto mMainLayout = t.findChild<QHBoxLayout *>(u"mMainLayout"_s);
    QVERIFY(mMainLayout);
    QCOMPARE(mMainLayout->contentsMargins(), QMargins{});
    QCOMPARE(mMainLayout->spacing(), 0);

    auto boldButton = t.findChild<QToolButton *>(u"boldButton"_s);
    QVERIFY(boldButton);
    QCOMPARE(boldButton->iconSize(), QSize(12, 12));
    QVERIFY(boldButton->autoRaise());
    QVERIFY(!boldButton->toolTip().isEmpty());
    QCOMPARE(boldButton->focusPolicy(), Qt::NoFocus);

    auto italicButton = t.findChild<QToolButton *>(u"italicButton"_s);
    QVERIFY(italicButton);
    QCOMPARE(italicButton->iconSize(), QSize(12, 12));
    QVERIFY(italicButton->autoRaise());
    QVERIFY(!italicButton->toolTip().isEmpty());
    QCOMPARE(italicButton->focusPolicy(), Qt::NoFocus);

    auto strikeThroughButton = t.findChild<QToolButton *>(u"strikeThroughButton"_s);
    QVERIFY(strikeThroughButton);
    QCOMPARE(strikeThroughButton->iconSize(), QSize(12, 12));
    QVERIFY(strikeThroughButton->autoRaise());
    QVERIFY(!strikeThroughButton->toolTip().isEmpty());
    QCOMPARE(strikeThroughButton->focusPolicy(), Qt::NoFocus);

    auto blockQuoteButton = t.findChild<QToolButton *>(u"blockQuoteButton"_s);
    QVERIFY(blockQuoteButton);
    QCOMPARE(blockQuoteButton->iconSize(), QSize(12, 12));
    QVERIFY(blockQuoteButton->autoRaise());
    QVERIFY(!blockQuoteButton->toolTip().isEmpty());
    QCOMPARE(blockQuoteButton->focusPolicy(), Qt::NoFocus);

    auto insertLinkButton = t.findChild<QToolButton *>(u"insertLinkButton"_s);
    QVERIFY(insertLinkButton);
    QCOMPARE(insertLinkButton->iconSize(), QSize(12, 12));
    QVERIFY(insertLinkButton->autoRaise());
    QVERIFY(!insertLinkButton->toolTip().isEmpty());
    QCOMPARE(insertLinkButton->focusPolicy(), Qt::NoFocus);

    auto underlineButton = t.findChild<QToolButton *>(u"underlineButton"_s);
    QVERIFY(underlineButton);
    QCOMPARE(underlineButton->iconSize(), QSize(12, 12));
    QVERIFY(underlineButton->autoRaise());
    QVERIFY(!underlineButton->toolTip().isEmpty());
    QCOMPARE(underlineButton->focusPolicy(), Qt::NoFocus);
}

void RichTextQuickTextFormatTest::shouldReactSignalCall()
{
    // Initialize all buttons
    TextAddonsWidgets::RichTextQuickTextFormat t(nullptr);
    TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatTypes formatTypes = TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::Unknown;
    formatTypes |= TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::Bold;
    formatTypes |= TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::Italic;
    formatTypes |= TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::StrikeThrough;
    formatTypes |= TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::BlockQuote;
    formatTypes |= TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::InsertLink;
    formatTypes |= TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::CodeBlock;
    formatTypes |= TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::UnderLine;
    t.setFormatTypes(formatTypes);
    {
        auto boldButton = t.findChild<QToolButton *>(u"boldButton"_s);
        QSignalSpy spyBoldButton(&t, &TextAddonsWidgets::RichTextQuickTextFormat::quickTextFormatRequested);
        QTest::mouseClick(boldButton, Qt::LeftButton);
        QCOMPARE(spyBoldButton.count(), 1);
        QCOMPARE(spyBoldButton.at(0).at(0).value<TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType>(),
                 TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::Bold);
    }
    {
        auto italicButton = t.findChild<QToolButton *>(u"italicButton"_s);
        QSignalSpy spyButton(&t, &TextAddonsWidgets::RichTextQuickTextFormat::quickTextFormatRequested);
        QTest::mouseClick(italicButton, Qt::LeftButton);
        QCOMPARE(spyButton.count(), 1);
        QCOMPARE(spyButton.at(0).at(0).value<TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType>(),
                 TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::Italic);
    }
    {
        auto strikeThroughButton = t.findChild<QToolButton *>(u"strikeThroughButton"_s);
        QSignalSpy spyButton(&t, &TextAddonsWidgets::RichTextQuickTextFormat::quickTextFormatRequested);
        QTest::mouseClick(strikeThroughButton, Qt::LeftButton);
        QCOMPARE(spyButton.count(), 1);
        QCOMPARE(spyButton.at(0).at(0).value<TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType>(),
                 TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::StrikeThrough);
    }
    {
        auto blockQuoteButton = t.findChild<QToolButton *>(u"blockQuoteButton"_s);
        QSignalSpy spyButton(&t, &TextAddonsWidgets::RichTextQuickTextFormat::quickTextFormatRequested);
        QTest::mouseClick(blockQuoteButton, Qt::LeftButton);
        QCOMPARE(spyButton.count(), 1);
        QCOMPARE(spyButton.at(0).at(0).value<TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType>(),
                 TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::BlockQuote);
    }
    {
        auto insertLinkButton = t.findChild<QToolButton *>(u"insertLinkButton"_s);
        QSignalSpy spyButton(&t, &TextAddonsWidgets::RichTextQuickTextFormat::quickTextFormatRequested);
        QTest::mouseClick(insertLinkButton, Qt::LeftButton);
        QCOMPARE(spyButton.count(), 1);
        QCOMPARE(spyButton.at(0).at(0).value<TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType>(),
                 TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::InsertLink);
    }
    {
        auto underlineButton = t.findChild<QToolButton *>(u"underlineButton"_s);
        QSignalSpy spyButton(&t, &TextAddonsWidgets::RichTextQuickTextFormat::quickTextFormatRequested);
        QTest::mouseClick(underlineButton, Qt::LeftButton);
        QCOMPARE(spyButton.count(), 1);
        QCOMPARE(spyButton.at(0).at(0).value<TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType>(),
                 TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::UnderLine);
    }
}

void RichTextQuickTextFormatTest::shouldSelectionSpecificFormatType()
{
    TextAddonsWidgets::RichTextQuickTextFormat t(nullptr);
    TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatTypes formatTypes = TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::Unknown;
    formatTypes |= TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::Bold;
    formatTypes |= TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::Italic;
    t.setFormatTypes(formatTypes);

    auto boldButton = t.findChild<QToolButton *>(u"boldButton"_s);
    QVERIFY(boldButton);

    auto italicButton = t.findChild<QToolButton *>(u"italicButton"_s);
    QVERIFY(italicButton);

    auto strikeThroughButton = t.findChild<QToolButton *>(u"strikeThroughButton"_s);
    QVERIFY(!strikeThroughButton);

    auto blockQuoteButton = t.findChild<QToolButton *>(u"blockQuoteButton"_s);
    QVERIFY(!blockQuoteButton);

    auto insertLinkButton = t.findChild<QToolButton *>(u"insertLinkButton"_s);
    QVERIFY(!insertLinkButton);

    auto underlineButton = t.findChild<QToolButton *>(u"underlineButton"_s);
    QVERIFY(!underlineButton);
}

#include "moc_richtextquicktextformattest.cpp"
