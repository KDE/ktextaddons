/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalecteconfigwidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "grammalecte/grammalecteconfigwidget.h"
#include "grammalecte/grammalecteurlrequesterwidget.h"
#include <QFormLayout>
#include <QLabel>
#include <QScrollArea>
#include <QStackedWidget>
#include <QStandardPaths>
#include <QTabWidget>
#include <QTest>
#include <QToolButton>
#include <QVBoxLayout>
QTEST_MAIN(GrammalecteConfigWidgetTest)
GrammalecteConfigWidgetTest::GrammalecteConfigWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void GrammalecteConfigWidgetTest::shouldHaveDefaultValue()
{
    TextGrammarCheck::GrammalecteConfigWidget w(nullptr, true);
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    auto mTab = w.findChild<QTabWidget *>(u"mTab"_s);
    QVERIFY(mTab);

    auto generalWidget = mTab->findChild<QWidget *>(u"general"_s);
    QVERIFY(generalWidget);
    auto lay = generalWidget->findChild<QFormLayout *>(u"generallayout"_s);
    QVERIFY(lay);

    auto mPythonPath = generalWidget->findChild<TextGrammarCheck::GrammalecteUrlRequesterWidget *>(u"pythonpath"_s);
    QVERIFY(mPythonPath);
    QVERIFY(!mPythonPath->path().isEmpty());

    auto mGrammalectePath = generalWidget->findChild<TextGrammarCheck::GrammalecteUrlRequesterWidget *>(u"grammalectepath"_s);
    QVERIFY(mGrammalectePath);
    QVERIFY(mGrammalectePath->path().isEmpty());

    auto grammalecteInfoDownload = generalWidget->findChild<QLabel *>(u"grammalecteInfoDownload"_s);
    QVERIFY(grammalecteInfoDownload);
    QVERIFY(!grammalecteInfoDownload->text().isEmpty());
    QVERIFY(grammalecteInfoDownload->openExternalLinks());
    QCOMPARE(grammalecteInfoDownload->textFormat(), Qt::RichText);

    auto mStackedWidget = mTab->findChild<QStackedWidget *>(u"stackedwidget"_s);
    QVERIFY(mStackedWidget);
    auto mScrollArea = mStackedWidget->findChild<QScrollArea *>(u"scrollarea"_s);
    QVERIFY(mScrollArea);
    QVERIFY(mScrollArea->widget());
    QCOMPARE(mScrollArea->widget()->objectName(), u"grammar"_s);

    auto mReloadSettingsWidget = mStackedWidget->findChild<QWidget *>(u"reloadwidget"_s);
    QVERIFY(mReloadSettingsWidget);

    auto reloadSettingsLayout = mReloadSettingsWidget->findChild<QVBoxLayout *>(u"reloadSettingsLayout"_s);
    QVERIFY(reloadSettingsLayout);

    auto label = mReloadSettingsWidget->findChild<QLabel *>(u"label"_s);
    QVERIFY(label);
    QVERIFY(!label->text().isEmpty());
    auto buttonReloadSettings = mReloadSettingsWidget->findChild<QToolButton *>(u"buttonReloadSettings"_s);
    QVERIFY(buttonReloadSettings);
    // QVERIFY(!buttonReloadSettings->icon().isNull());
}

#include "moc_grammalecteconfigwidgettest.cpp"
