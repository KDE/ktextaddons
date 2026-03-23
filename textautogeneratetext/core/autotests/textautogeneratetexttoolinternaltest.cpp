/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetexttoolinternaltest.h"
#include "core/tools/textautogeneratetexttoolinternal.h"
#include "core/tools/textautogeneratetexttoolinternalproperty.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateTextToolInternalTest)

TextAutoGenerateTextToolInternalTest::TextAutoGenerateTextToolInternalTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextToolInternalTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateTextToolInternal w;
    QVERIFY(w.properties().isEmpty());
    QVERIFY(w.required().isEmpty());
}
