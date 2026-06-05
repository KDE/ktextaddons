/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textmessageindicatortest.h"
#include "widgets/textmessageindicator.h"

#include <QTest>
QTEST_MAIN(TextMessageIndicatorTest)

TextMessageIndicatorTest::TextMessageIndicatorTest(QObject *parent)
    : QObject{parent}
{
}

void TextMessageIndicatorTest::shouldHaveDefaultValues()
{
    // TODO
    TextCustomEditor::TextMessageIndicator w;
}
