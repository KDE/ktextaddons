/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "translatorconfigurewidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "translator/widgets/translatorconfigurecombowidget.h"
#include "translator/widgets/translatorconfigurewidget.h"
#include <QLabel>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TranslatorConfigureWidgetTest)
TranslatorConfigureWidgetTest::TranslatorConfigureWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TranslatorConfigureWidgetTest::shouldHaveDefaultValues()
{
    TextTranslator::TranslatorConfigureWidget w;

    auto mEngineConfigureComboWidget = w.findChild<TextTranslator::TranslatorConfigureComboWidget *>(u"mEngineConfigureComboWidget"_s);
    QVERIFY(mEngineConfigureComboWidget);

    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto label = w.findChild<QLabel *>(u"label"_s);
    QVERIFY(label);
    QVERIFY(!label->text().isEmpty());
}

#include "moc_translatorconfigurewidgettest.cpp"
