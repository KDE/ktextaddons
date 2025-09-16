/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetoolpluginconfigurewidgettest.h"
#include "widgets/configuretoolsplugin/textautogeneratetoolpluginconfigurewidget.h"
#include <QLabel>
#include <QTest>
#include <QToolButton>
#include <QVBoxLayout>

QTEST_MAIN(TextAutoGenerateToolPluginConfigureWidgetTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateToolPluginConfigureWidgetTest::TextAutoGenerateToolPluginConfigureWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateToolPluginConfigureWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateToolPluginConfigureWidget w(nullptr);

    auto mainLayout = w.findChild<QVBoxLayout *>("mainLayout"_L1);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mDescriptionLabel = w.findChild<QLabel *>("mDescriptionLabel"_L1);
    QVERIFY(mDescriptionLabel);
    auto mArgumentsLabel = w.findChild<QLabel *>("mArgumentsLabel"_L1);
    QVERIFY(mArgumentsLabel);
    auto mInfoToolButton = w.findChild<QToolButton *>("mInfoToolButton"_L1);
    QVERIFY(mInfoToolButton);
    QVERIFY(!mInfoToolButton->toolTip().isEmpty());
    QCOMPARE(mInfoToolButton->focusPolicy(), Qt::NoFocus);
}

#include "moc_textautogeneratetoolpluginconfigurewidgettest.cpp"
