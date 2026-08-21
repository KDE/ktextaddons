/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextlineeditattachmentwidgettest.h"
#include "widgets/common/textautogeneratetextlineeditattachmentwidget.h"
#include <TextAddonsWidgets/TextAddonsWidgetFlowLayout>

#include <QStandardPaths>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_MAIN(TextAutoGenerateTextLineEditAttachmentWidgetTest)
TextAutoGenerateTextLineEditAttachmentWidgetTest::TextAutoGenerateTextLineEditAttachmentWidgetTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutoGenerateTextLineEditAttachmentWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateTextLineEditAttachmentWidget w;

    auto mainLayout = w.findChild<TextAddonsWidgets::TextAddonsWidgetFlowLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(w.contentsMargins(), QMargins{});

    // TODO
}

#include "moc_textautogeneratetextlineeditattachmentwidgettest.cpp"
