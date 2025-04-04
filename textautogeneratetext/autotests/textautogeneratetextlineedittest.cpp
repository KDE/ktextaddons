/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextlineedittest.h"
#include "widgets/textautogeneratetextlineedit.h"
#include <QTest>
QTEST_MAIN(TextAutogenerateTextLineEditTest)

TextAutogenerateTextLineEditTest::TextAutogenerateTextLineEditTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutogenerateTextLineEditTest::shouldHaveDefaultValues()
{
    TextAutogenerateText::TextAutogenerateTextLineEdit d;
    QVERIFY(d.text().isEmpty());
    QVERIFY(d.placeholderText().isEmpty());
    QVERIFY(!d.acceptRichText());
    QVERIFY(d.tabChangesFocus());
}

#include "moc_textautogeneratetextlineedittest.cpp"
