/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratechattest.h"
#include "core/textautogeneratechat.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateChatTest)

TextAutoGenerateChatTest::TextAutoGenerateChatTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateChatTest::shouldHaveDefaultValues()
{
    TextAutogenerateText::TextAutoGenerateChat w;
    QVERIFY(!w.favorite());
}
