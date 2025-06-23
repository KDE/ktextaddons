/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "translatorconfigurelanguagelistwidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "translator/widgets/translatorconfigurelanguagelistwidget.h"
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TranslatorConfigureLanguageListWidgetTest)
TranslatorConfigureLanguageListWidgetTest::TranslatorConfigureLanguageListWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TranslatorConfigureLanguageListWidgetTest::shouldHaveDefaultValues()
{
    TextTranslator::TranslatorConfigureLanguageListWidget w({});
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mLanguageListWidget = w.findChild<QListView *>(u"mLanguageListWidget"_s);
    QVERIFY(mLanguageListWidget);

    auto mListSearchLine = w.findChild<QLineEdit *>(u"mListSearchLine"_s);
    QVERIFY(mListSearchLine);
    QVERIFY(!mListSearchLine->placeholderText().isEmpty());

    auto mLabel = w.findChild<QLabel *>(u"mLabel"_s);
    QVERIFY(mLabel);
    QVERIFY(mLabel->text().isEmpty());
    QVERIFY(w.selectedLanguages().isEmpty());
}

void TranslatorConfigureLanguageListWidgetTest::shouldAssignLabel()
{
    const QString label{u"FOO"_s};
    TextTranslator::TranslatorConfigureLanguageListWidget w(label);
    auto mLabel = w.findChild<QLabel *>(u"mLabel"_s);
    QVERIFY(mLabel);
    QCOMPARE(mLabel->text(), label);
}

#include "moc_translatorconfigurelanguagelistwidgettest.cpp"
