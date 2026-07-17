/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextlineeditattachmentclickablewidgettest.h"
#include "widgets/common/textautogeneratetextlineeditattachmentclickablewidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QTest>
#include <QToolButton>
using namespace Qt::Literals::StringLiterals;

QTEST_MAIN(TextAutoGenerateTextLineEditAttachmentClickableWidgetTest)
TextAutoGenerateTextLineEditAttachmentClickableWidgetTest::TextAutoGenerateTextLineEditAttachmentClickableWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextLineEditAttachmentClickableWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateTextLineEditAttachmentClickableWidget w({});

    auto mainLayout = w.findChild<QHBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mFileNameLabel = w.findChild<QLabel *>(u"mFileNameLabel"_s);
    QVERIFY(mFileNameLabel);

    auto mMimetypeLabel = w.findChild<QLabel *>(u"mMimetypeLabel"_s);
    QVERIFY(mMimetypeLabel);

    auto removeBtn = w.findChild<QToolButton *>(u"removeBtn"_s);
    QVERIFY(removeBtn);
    QVERIFY(removeBtn->autoRaise());
    QVERIFY(!removeBtn->toolTip().isEmpty());
}

#include "moc_textautogeneratetextlineeditattachmentclickablewidgettest.cpp"
