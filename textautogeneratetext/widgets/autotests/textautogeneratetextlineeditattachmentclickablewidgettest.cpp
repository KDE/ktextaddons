/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextlineeditattachmentclickablewidgettest.h"
#include "widgets/common/textautogeneratetextlineeditattachmentclickablewidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QTest>
using namespace Qt::Literals::StringLiterals;

QTEST_MAIN(TextAutoGenerateTextLineEditAttachmentClickableWidgetTest)
TextAutoGenerateTextLineEditAttachmentClickableWidgetTest::TextAutoGenerateTextLineEditAttachmentClickableWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextLineEditAttachmentClickableWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateTextLineEditAttachmentClickableWidget w({});

    auto mainLayout = w.findChild<QHBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mClickableLabel = w.findChild<TextAutoGenerateText::TextAutoGenerateTextLineEditAttachmentClickableLabel *>(u"mClickableLabel"_s);
    QVERIFY(mClickableLabel);

    auto mFileNameLabel = w.findChild<QLabel *>(u"mFileNameLabel"_s);
    QVERIFY(mFileNameLabel);

    auto mMimetypeLabel = w.findChild<QLabel *>(u"mMimetypeLabel"_s);
    QVERIFY(mMimetypeLabel);
}

#include "moc_textautogeneratetextlineeditattachmentclickablewidgettest.cpp"
