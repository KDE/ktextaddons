/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetagwidgettest.h"
#include "widgets/tags/textautogeneratetagwidget.h"
#include <KColorButton>
#include <QFormLayout>
#include <QLineEdit>
#include <QSignalSpy>
#include <QTest>
QTEST_MAIN(TextAutoGenerateTagWidgetTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateTagWidgetTest::TextAutoGenerateTagWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTagWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateTagWidget w;
    auto mainLayout = w.findChild<QFormLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mName = w.findChild<QLineEdit *>(u"mName"_s);
    QVERIFY(mName);
    QVERIFY(mName->text().isEmpty());
    QVERIFY(mName->isClearButtonEnabled());
    QVERIFY(!mName->placeholderText().isEmpty());

    auto mColor = w.findChild<KColorButton *>(u"mColor"_s);
    QVERIFY(mColor);
    QVERIFY(!mColor->isAlphaChannelEnabled());
}

void TextAutoGenerateTagWidgetTest::shouldKeepIdentifierWhenEditingTag()
{
    // GIVEN
    TextAutoGenerateText::TextAutoGenerateTagWidget w;
    TextAutoGenerateText::TextAutoGenerateTag tag;
    tag.setIdentifier("tag1");
    tag.setName(u"name-tag1"_s);
    tag.setColor(QColor(Qt::red));
    w.setTag(tag);

    auto mName = w.findChild<QLineEdit *>(u"mName"_s);
    QVERIFY(mName);
    QCOMPARE(mName->text(), u"name-tag1"_s);
    auto mColor = w.findChild<KColorButton *>(u"mColor"_s);
    QVERIFY(mColor);
    QCOMPARE(mColor->color(), QColor(Qt::red));

    // WHEN
    mName->setText(u"  renamed  "_s);
    mColor->setColor(QColor(Qt::blue));

    // THEN
    const TextAutoGenerateText::TextAutoGenerateTag result = w.tag();
    QCOMPARE(result.identifier(), "tag1"_ba);
    QCOMPARE(result.name(), u"renamed"_s);
    QCOMPARE(result.color(), QColor(Qt::blue));
}

void TextAutoGenerateTagWidgetTest::shouldEmitEnableOkButton()
{
    TextAutoGenerateText::TextAutoGenerateTagWidget w;
    QSignalSpy enableOkButtonSpy(&w, &TextAutoGenerateText::TextAutoGenerateTagWidget::enableOkButton);
    auto mName = w.findChild<QLineEdit *>(u"mName"_s);
    QVERIFY(mName);

    mName->setText(u"foo"_s);
    QCOMPARE(enableOkButtonSpy.count(), 1);
    QVERIFY(enableOkButtonSpy.at(0).at(0).toBool());

    // Whitespace only is not a name.
    mName->setText(u"   "_s);
    QCOMPARE(enableOkButtonSpy.count(), 2);
    QVERIFY(!enableOkButtonSpy.at(1).at(0).toBool());
}
#include "moc_textautogeneratetagwidgettest.cpp"
