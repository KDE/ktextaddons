/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextlineedittest.h"
#include "widgets/common/textautogeneratetextlineedit.h"
#include <QTest>
QTEST_MAIN(TextAutoGenerateTextLineEditTest)

TextAutoGenerateTextLineEditTest::TextAutoGenerateTextLineEditTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextLineEditTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateTextLineEdit d;
    QVERIFY(d.text().isEmpty());
    QVERIFY(!d.placeholderText().isEmpty());
    QVERIFY(!d.acceptRichText());
    QVERIFY(d.tabChangesFocus());
}

#include "moc_textautogeneratetextlineedittest.cpp"
