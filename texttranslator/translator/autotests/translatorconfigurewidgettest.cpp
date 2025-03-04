/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "translatorconfigurewidgettest.h"
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

    auto mEngineConfigureComboWidget = w.findChild<TextTranslator::TranslatorConfigureComboWidget *>(QStringLiteral("mEngineConfigureComboWidget"));
    QVERIFY(mEngineConfigureComboWidget);

    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto label = w.findChild<QLabel *>(QStringLiteral("label"));
    QVERIFY(label);
    QVERIFY(!label->text().isEmpty());
}

#include "moc_translatorconfigurewidgettest.cpp"
