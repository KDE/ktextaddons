/*
   SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalecteconfigwidgettest.h"
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
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    auto mTab = w.findChild<QTabWidget *>(QStringLiteral("mTab"));
    QVERIFY(mTab);

    auto generalWidget = mTab->findChild<QWidget *>(QStringLiteral("general"));
    QVERIFY(generalWidget);
    auto lay = generalWidget->findChild<QFormLayout *>(QStringLiteral("generallayout"));
    QVERIFY(lay);

    auto mPythonPath = generalWidget->findChild<TextGrammarCheck::GrammalecteUrlRequesterWidget *>(QStringLiteral("pythonpath"));
    QVERIFY(mPythonPath);
    QVERIFY(!mPythonPath->path().isEmpty());

    auto mGrammalectePath = generalWidget->findChild<TextGrammarCheck::GrammalecteUrlRequesterWidget *>(QStringLiteral("grammalectepath"));
    QVERIFY(mGrammalectePath);
    QVERIFY(mGrammalectePath->path().isEmpty());

    auto grammalecteInfoDownload = generalWidget->findChild<QLabel *>(QStringLiteral("grammalecteInfoDownload"));
    QVERIFY(grammalecteInfoDownload);
    QVERIFY(!grammalecteInfoDownload->text().isEmpty());
    QVERIFY(grammalecteInfoDownload->openExternalLinks());
    QCOMPARE(grammalecteInfoDownload->textFormat(), Qt::RichText);

    auto mStackedWidget = mTab->findChild<QStackedWidget *>(QStringLiteral("stackedwidget"));
    QVERIFY(mStackedWidget);
    auto mScrollArea = mStackedWidget->findChild<QScrollArea *>(QStringLiteral("scrollarea"));
    QVERIFY(mScrollArea);
    QVERIFY(mScrollArea->widget());
    QCOMPARE(mScrollArea->widget()->objectName(), QStringLiteral("grammar"));

    auto mReloadSettingsWidget = mStackedWidget->findChild<QWidget *>(QStringLiteral("reloadwidget"));
    QVERIFY(mReloadSettingsWidget);

    auto reloadSettingsLayout = mReloadSettingsWidget->findChild<QVBoxLayout *>(QStringLiteral("reloadSettingsLayout"));
    QVERIFY(reloadSettingsLayout);

    auto label = mReloadSettingsWidget->findChild<QLabel *>(QStringLiteral("label"));
    QVERIFY(label);
    QVERIFY(!label->text().isEmpty());
    auto buttonReloadSettings = mReloadSettingsWidget->findChild<QToolButton *>(QStringLiteral("buttonReloadSettings"));
    QVERIFY(buttonReloadSettings);
    QVERIFY(!buttonReloadSettings->icon().isNull());
}

#include "moc_grammalecteconfigwidgettest.cpp"
