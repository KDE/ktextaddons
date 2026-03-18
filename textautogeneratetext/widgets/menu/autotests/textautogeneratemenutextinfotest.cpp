/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogeneratemenutextinfotest.h"
#include "widgets/menu/textautogeneratemenutextinfo.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateMenuTextInfoTest)

TextAutoGenerateMenuTextInfoTest::TextAutoGenerateMenuTextInfoTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateMenuTextInfoTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateMenuTextInfo info;
    QVERIFY(info.enabled());
    QVERIFY(info.requestText().isEmpty());
    QCOMPARE(info.order(), 0);
}

#include "moc_textautogeneratemenutextinfotest.cpp"
