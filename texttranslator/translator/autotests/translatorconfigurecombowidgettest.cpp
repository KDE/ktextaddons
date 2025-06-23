/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "translatorconfigurecombowidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "translator/widgets/translatorconfigurecombowidget.h"
#include <QComboBox>
#include <QHBoxLayout>
#include <QStandardPaths>
#include <QTest>
#include <QToolButton>
QTEST_MAIN(TranslatorConfigureComboWidgetTest)
TranslatorConfigureComboWidgetTest::TranslatorConfigureComboWidgetTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TranslatorConfigureComboWidgetTest::shouldHaveDefaultValues()
{
    TextTranslator::TranslatorConfigureComboWidget d;
    auto mEngineComboBox = d.findChild<QComboBox *>(u"mEngineComboBox"_s);
    QVERIFY(mEngineComboBox);
    auto mConfigureEngine = d.findChild<QToolButton *>(u"mConfigureEngine"_s);
    QVERIFY(mConfigureEngine);

    auto mainLayout = d.findChild<QHBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    // FIXME it depends against plugin. First is bergamot => enabled. Before google => disable
    // QVERIFY(!mConfigureEngine->isEnabled());
}

#include "moc_translatorconfigurecombowidgettest.cpp"
