/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateattachmentstest.h"
#include "core/textautogenerateattachments.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateAttachmentsTest)

TextAutoGenerateAttachmentsTest::TextAutoGenerateAttachmentsTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateAttachmentsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateAttachments w;
    QVERIFY(w.isEmpty());

    // 11/03/2025 => size 32
    QCOMPARE(sizeof(TextAutoGenerateText::TextAutoGenerateAttachments), 32);
}
