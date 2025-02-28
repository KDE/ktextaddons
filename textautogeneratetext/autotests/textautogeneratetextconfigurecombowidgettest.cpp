/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "textautogeneratetextconfigurecombowidgettest.h"
#include "widgets/textautogeneratetextconfigurecombowidget.h"
#include <QComboBox>
#include <QHBoxLayout>
#include <QStandardPaths>
#include <QTest>
#include <QToolButton>
QTEST_MAIN(TextAutogenerateTextConfigureComboWidgetTest)

TextAutogenerateTextConfigureComboWidgetTest::TextAutogenerateTextConfigureComboWidgetTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutogenerateTextConfigureComboWidgetTest::shouldHaveDefaultValues()
{
    TextAutogenerateText::TextAutogenerateTextConfigureComboWidget d;
    auto mEngineComboBox = d.findChild<QComboBox *>(QStringLiteral("mEngineComboBox"));
    QVERIFY(mEngineComboBox);
    auto mConfigureEngine = d.findChild<QToolButton *>(QStringLiteral("mConfigureEngine"));
    QVERIFY(mConfigureEngine);

    auto mainLayout = d.findChild<QHBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});
    // TODO
}
