/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateshowmodelinfowidgettest.h"
#include "widgets/common/textautogenerateshowmodelinfowidget.h"
#include <QTest>
#include <QTextEdit>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateShowModelInfoWidgetTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateShowModelInfoWidgetTest::TextAutoGenerateShowModelInfoWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateShowModelInfoWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateShowModelInfoWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mTextEdit = w.findChild<QTextEdit *>(u"mTextEdit"_s);
    QVERIFY(mTextEdit);
    QVERIFY(mTextEdit->isReadOnly());
}

#include "moc_textautogenerateshowmodelinfowidgettest.cpp"
