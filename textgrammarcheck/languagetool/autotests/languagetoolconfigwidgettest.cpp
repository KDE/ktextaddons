/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolconfigwidgettest.h"
#include "languagetool/languagetoolcombobox.h"
#include "languagetool/languagetoolconfigwidget.h"
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QStandardPaths>
#include <QTest>
#include <QToolButton>
#include <QVBoxLayout>
#include <qtestmouse.h>

QTEST_MAIN(LanguageToolConfigWidgetTest)
LanguageToolConfigWidgetTest::LanguageToolConfigWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void LanguageToolConfigWidgetTest::shouldHaveDefaultValue()
{
    TextGrammarCheck::LanguageToolConfigWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    auto mUseLocalInstance = w.findChild<QCheckBox *>(QStringLiteral("uselocalinstance"));
    QVERIFY(mUseLocalInstance);
    QVERIFY(!mUseLocalInstance->text().isEmpty());
    QVERIFY(!mUseLocalInstance->isChecked());

    auto instancePathLabel = w.findChild<QLabel *>(QStringLiteral("instancepath"));
    QVERIFY(instancePathLabel);
    QVERIFY(!instancePathLabel->text().isEmpty());
    QVERIFY(!instancePathLabel->isEnabled());

    auto mInstancePath = w.findChild<QLineEdit *>(QStringLiteral("instancepath"));
    QVERIFY(mInstancePath);
    // We load default value
    QVERIFY(!mInstancePath->text().isEmpty());
    QVERIFY(!mInstancePath->isEnabled());
    QVERIFY(mInstancePath->isClearButtonEnabled());

    auto languageLabel = w.findChild<QLabel *>(QStringLiteral("languageLabel"));
    QVERIFY(languageLabel);
    QVERIFY(!languageLabel->text().isEmpty());

    auto mLanguageToolCombobox = w.findChild<TextGrammarCheck::LanguageToolComboBox *>(QStringLiteral("languagecombobox"));
    QVERIFY(mLanguageToolCombobox);

    auto refreshButton = w.findChild<QToolButton *>(QStringLiteral("refreshbutton"));
    QVERIFY(refreshButton);
    // QVERIFY(!refreshButton->icon().isNull());
}

void LanguageToolConfigWidgetTest::shouldUpdateWidgets()
{
    TextGrammarCheck::LanguageToolConfigWidget w;

    auto mUseLocalInstance = w.findChild<QCheckBox *>(QStringLiteral("uselocalinstance"));

    auto instancePathLabel = w.findChild<QLabel *>(QStringLiteral("instancepath"));

    auto mInstancePath = w.findChild<QLineEdit *>(QStringLiteral("instancepath"));
    QTest::mouseClick(mUseLocalInstance, Qt::LeftButton);

    QVERIFY(mUseLocalInstance->isChecked());
    QVERIFY(mUseLocalInstance->isEnabled());
    QVERIFY(instancePathLabel->isEnabled());
    QVERIFY(mInstancePath->isEnabled());

    QTest::mouseClick(mUseLocalInstance, Qt::LeftButton);
    QVERIFY(!mUseLocalInstance->isChecked());
    QVERIFY(mUseLocalInstance->isEnabled());
    QVERIFY(!instancePathLabel->isEnabled());
    QVERIFY(!mInstancePath->isEnabled());
}

#include "moc_languagetoolconfigwidgettest.cpp"
