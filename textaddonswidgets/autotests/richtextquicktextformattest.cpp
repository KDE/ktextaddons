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
    const TextAddonsWidgets::RichTextQuickTextFormat t(nullptr);
    QCOMPARE(t.focusPolicy(), Qt::NoFocus);

    auto mMainLayout = t.findChild<QHBoxLayout *>(u"mMainLayout"_s);
    QVERIFY(mMainLayout);
    QCOMPARE(mMainLayout->contentsMargins(), QMargins{});
    QCOMPARE(mMainLayout->spacing(), 0);

    auto boldButton = t.findChild<QToolButton *>(u"boldButton"_s);
    QCOMPARE(boldButton->iconSize(), QSize(12, 12));
    QVERIFY(boldButton->autoRaise());
    QVERIFY(!boldButton->toolTip().isEmpty());
    QCOMPARE(boldButton->focusPolicy(), Qt::NoFocus);

    auto italicButton = t.findChild<QToolButton *>(u"italicButton"_s);
    QCOMPARE(italicButton->iconSize(), QSize(12, 12));
    QVERIFY(italicButton->autoRaise());
    QVERIFY(!italicButton->toolTip().isEmpty());
    QCOMPARE(italicButton->focusPolicy(), Qt::NoFocus);

    auto strikeThroughButton = t.findChild<QToolButton *>(u"strikeThroughButton"_s);
    QCOMPARE(strikeThroughButton->iconSize(), QSize(12, 12));
    QVERIFY(strikeThroughButton->autoRaise());
    QVERIFY(!strikeThroughButton->toolTip().isEmpty());
    QCOMPARE(strikeThroughButton->focusPolicy(), Qt::NoFocus);

    auto blockQuoteButton = t.findChild<QToolButton *>(u"blockQuoteButton"_s);
    QCOMPARE(blockQuoteButton->iconSize(), QSize(12, 12));
    QVERIFY(blockQuoteButton->autoRaise());
    QVERIFY(!blockQuoteButton->toolTip().isEmpty());
    QCOMPARE(blockQuoteButton->focusPolicy(), Qt::NoFocus);

    auto insertLinkButton = t.findChild<QToolButton *>(u"insertLinkButton"_s);
    QCOMPARE(insertLinkButton->iconSize(), QSize(12, 12));
    QVERIFY(insertLinkButton->autoRaise());
    QVERIFY(!insertLinkButton->toolTip().isEmpty());
    QCOMPARE(insertLinkButton->focusPolicy(), Qt::NoFocus);
}

void RichTextQuickTextFormatTest::shouldReactSignalCall()
{
    const TextAddonsWidgets::RichTextQuickTextFormat t(nullptr);
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
}

#include "moc_richtextquicktextformattest.cpp"
