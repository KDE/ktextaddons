/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetexttoolpluginpropertytest.h"
#include "core/tools/textautogeneratetexttoolpluginproperty.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateTextToolPluginPropertyTest)
TextAutoGenerateTextToolPluginPropertyTest::TextAutoGenerateTextToolPluginPropertyTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextToolPluginPropertyTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty w;
    QVERIFY(w.description().isEmpty());
    QVERIFY(w.name().isEmpty());
}
