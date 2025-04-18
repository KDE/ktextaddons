/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateheaderwidgettest.h"
#include "widgets/textautogenerateheaderwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QSignalSpy>
#include <QTest>
#include <QToolButton>
#include <qtestmouse.h>
QTEST_MAIN(TextAutogenerateHeaderWidgetTest)

TextAutogenerateHeaderWidgetTest::TextAutogenerateHeaderWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutogenerateHeaderWidgetTest::shouldHaveDefaultValues()
{
    TextAutogenerateText::TextAutogenerateHeaderWidget w;
    auto mainLayout = w.findChild<QHBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mEngineName = w.findChild<QLabel *>(QStringLiteral("mEngineName"));
    QVERIFY(mEngineName);
    QVERIFY(mEngineName->text().isEmpty());

    auto mConfigureEngine = w.findChild<QToolButton *>(QStringLiteral("mConfigureEngine"));
    QVERIFY(mConfigureEngine);
    QVERIFY(mConfigureEngine->autoRaise());
    QVERIFY(!mConfigureEngine->toolTip().isEmpty());

    auto mClearChat = w.findChild<QToolButton *>(QStringLiteral("mClearChat"));
    QVERIFY(mClearChat);
    QVERIFY(mClearChat->autoRaise());
    QVERIFY(!mClearChat->toolTip().isEmpty());
}

void TextAutogenerateHeaderWidgetTest::shouldReactWhenClickClearButton()
{
    TextAutogenerateText::TextAutogenerateHeaderWidget w;
    auto mClearChat = w.findChild<QToolButton *>(QStringLiteral("mClearChat"));

    QSignalSpy clarModelSpy(&w, &TextAutogenerateText::TextAutogenerateHeaderWidget::clearModel);
    QTest::mouseClick(mClearChat, Qt::LeftButton);
    QCOMPARE(clarModelSpy.count(), 1);
}

#include "moc_textautogenerateheaderwidgettest.cpp"
