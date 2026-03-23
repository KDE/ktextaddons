/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetexttoolinternalpropertytest.h"
#include "core/tools/textautogeneratetexttoolinternalproperty.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateTextToolInternalPropertyTest)

TextAutoGenerateTextToolInternalPropertyTest::TextAutoGenerateTextToolInternalPropertyTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextToolInternalPropertyTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty w;
    // TODO
}
