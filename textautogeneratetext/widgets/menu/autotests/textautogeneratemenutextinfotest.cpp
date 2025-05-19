/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

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
    TextAutoGenerateText::TextAutoGenerateMenuTextInfo info;
    QVERIFY(info.enabled());
    QVERIFY(info.requestText().isEmpty());
}

#include "moc_textautogeneratemenutextinfotest.cpp"
