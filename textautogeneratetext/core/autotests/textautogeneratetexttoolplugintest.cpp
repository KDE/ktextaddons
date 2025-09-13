/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetexttoolplugintest.h"
#include "core/tools/textautogeneratetexttoolplugin.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateTextToolPluginTest)

TextAutoGenerateTextToolPluginTest::TextAutoGenerateTextToolPluginTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextToolPluginTest::shouldHaveDefaultValues()
{
    // TODO
}

#include "moc_textautogeneratetexttoolplugintest.cpp"
