/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateprojectwidgettest.h"
#include "widgets/projects/textautogenerateprojectwidget.h"
#include <KColorButton>
#include <QFormLayout>
#include <QLineEdit>
#include <QSignalSpy>
#include <QTest>
QTEST_MAIN(TextAutoGenerateProjectWidgetTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateProjectWidgetTest::TextAutoGenerateProjectWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateProjectWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateProjectWidget w;
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

void TextAutoGenerateProjectWidgetTest::shouldKeepIdentifierWhenEditingProject()
{
    // GIVEN
    TextAutoGenerateText::TextAutoGenerateProjectWidget w;
    TextAutoGenerateText::TextAutoGenerateProject project;
    project.setIdentifier("project1");
    project.setName(u"name-project1"_s);
    project.setColor(QColor(Qt::red));
    w.setProject(project);

    auto mName = w.findChild<QLineEdit *>(u"mName"_s);
    QVERIFY(mName);
    QCOMPARE(mName->text(), u"name-project1"_s);
    auto mColor = w.findChild<KColorButton *>(u"mColor"_s);
    QVERIFY(mColor);
    QCOMPARE(mColor->color(), QColor(Qt::red));

    // WHEN
    mName->setText(u"  renamed  "_s);
    mColor->setColor(QColor(Qt::blue));

    // THEN
    const TextAutoGenerateText::TextAutoGenerateProject result = w.project();
    QCOMPARE(result.identifier(), "project1"_ba);
    QCOMPARE(result.name(), u"renamed"_s);
    QCOMPARE(result.color(), QColor(Qt::blue));
}

void TextAutoGenerateProjectWidgetTest::shouldEmitEnableOkButton()
{
    TextAutoGenerateText::TextAutoGenerateProjectWidget w;
    QSignalSpy enableOkButtonSpy(&w, &TextAutoGenerateText::TextAutoGenerateProjectWidget::enableOkButton);
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
#include "moc_textautogenerateprojectwidgettest.cpp"
