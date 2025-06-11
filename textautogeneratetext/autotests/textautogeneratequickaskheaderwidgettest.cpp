/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratequickaskheaderwidgettest.h"
#include "widgets/quickask/textautogeneratequickaskheaderwidget.h"
#include <QHBoxLayout>
#include <QSignalSpy>
#include <QTest>
#include <QToolButton>
#include <qtestmouse.h>
QTEST_MAIN(TextAutoGenerateQuickAskHeaderWidgetTest)

TextAutoGenerateQuickAskHeaderWidgetTest::TextAutoGenerateQuickAskHeaderWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateQuickAskHeaderWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateQuickAskHeaderWidget w(nullptr);

    auto mainLayout = w.findChild<QHBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto configureButton = w.findChild<QToolButton *>(QStringLiteral("configureButton"));
    QVERIFY(configureButton);
    QVERIFY(!configureButton->toolTip().isEmpty());
    QVERIFY(configureButton->autoRaise());
}
/*
    QSignalSpy spy(&w, &OllamaModelDownloadWidget::downloadModel);

    auto toolButton = w.findChild<QToolButton *>(QStringLiteral("toolButton"));
    QTest::mouseClick(toolButton, Qt::LeftButton);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toString(), name);
*/

#include "moc_textautogeneratequickaskheaderwidgettest.cpp"
