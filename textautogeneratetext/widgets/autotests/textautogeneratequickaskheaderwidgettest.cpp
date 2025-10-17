/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratequickaskheaderwidgettest.h"

#include "widgets/common/textautogeneratetextmodelcombobox.h"
#include "widgets/quickask/textautogeneratequickaskheaderwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QSignalSpy>
#include <QTest>
#include <QToolButton>
#include <qtestmouse.h>
QTEST_MAIN(TextAutoGenerateQuickAskHeaderWidgetTest)

using namespace Qt::Literals::StringLiterals;
TextAutoGenerateQuickAskHeaderWidgetTest::TextAutoGenerateQuickAskHeaderWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateQuickAskHeaderWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateQuickAskHeaderWidget w(nullptr);

    auto mainLayout = w.findChild<QHBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mModelInstanceLabel = w.findChild<QLabel *>(u"mModelInstanceLabel"_s);
    QVERIFY(mModelInstanceLabel);
    QVERIFY(mModelInstanceLabel->text().isEmpty());

    auto configureButton = w.findChild<QToolButton *>(u"configureButton"_s);
    QVERIFY(configureButton);
    QVERIFY(!configureButton->toolTip().isEmpty());
    QVERIFY(configureButton->autoRaise());

    auto clearButton = w.findChild<QToolButton *>(u"clearButton"_s);
    QVERIFY(clearButton);
    QVERIFY(!clearButton->toolTip().isEmpty());
    QVERIFY(clearButton->autoRaise());

    auto saveQuickAskButton = w.findChild<QToolButton *>(u"saveQuickAskButton"_s);
    QVERIFY(saveQuickAskButton);
    QVERIFY(!saveQuickAskButton->toolTip().isEmpty());
    QVERIFY(saveQuickAskButton->autoRaise());

    auto searchButton = w.findChild<QToolButton *>(u"searchButton"_s);
    QVERIFY(searchButton);
    QVERIFY(!searchButton->toolTip().isEmpty());
    QVERIFY(searchButton->autoRaise());

    auto mModelComboBox = w.findChild<TextAutoGenerateText::TextAutoGenerateTextModelComboBox *>(u"mModelComboBox"_s);
    QVERIFY(mModelComboBox);
}

void TextAutoGenerateQuickAskHeaderWidgetTest::shouldEmitConfigureRequested()
{
    TextAutoGenerateText::TextAutoGenerateQuickAskHeaderWidget w(nullptr);

    QSignalSpy spy(&w, &TextAutoGenerateText::TextAutoGenerateQuickAskHeaderWidget::configureRequested);

    auto toolButton = w.findChild<QToolButton *>(u"configureButton"_s);
    QTest::mouseClick(toolButton, Qt::LeftButton);
    QCOMPARE(spy.count(), 1);
}

#include "moc_textautogeneratequickaskheaderwidgettest.cpp"
