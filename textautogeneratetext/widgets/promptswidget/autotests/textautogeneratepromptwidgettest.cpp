/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratepromptwidgettest.h"
#include "widgets/promptswidget/textautogeneratepromptwidget.h"
#include <KIconButton>
#include <QFormLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QSignalSpy>
#include <QStandardPaths>
#include <QTest>
QTEST_MAIN(TextAutoGeneratePromptWidgetTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGeneratePromptWidgetTest::TextAutoGeneratePromptWidgetTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutoGeneratePromptWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGeneratePromptWidget w;
    auto mainLayout = w.findChild<QFormLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mName = w.findChild<QLineEdit *>(u"mName"_s);
    QVERIFY(mName);
    QVERIFY(mName->text().isEmpty());

    auto mIconName = w.findChild<KIconButton *>(u"mIconName"_s);
    QVERIFY(mIconName);
    QVERIFY(mIconName->icon().isEmpty());

    auto mDescription = w.findChild<QPlainTextEdit *>(u"mDescription"_s);
    QVERIFY(mDescription);
    QVERIFY(mDescription->toPlainText().isEmpty());

    auto mPrompt = w.findChild<QPlainTextEdit *>(u"mPrompt"_s);
    QVERIFY(mPrompt);
    QVERIFY(mPrompt->toPlainText().isEmpty());
}

void TextAutoGeneratePromptWidgetTest::shouldEmitEnableOkButton()
{
    TextAutoGenerateText::TextAutoGeneratePromptWidget w;
    QSignalSpy enableOkButtonSpy(&w, &TextAutoGenerateText::TextAutoGeneratePromptWidget::enableOkButton);
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

#include "moc_textautogeneratepromptwidgettest.cpp"
