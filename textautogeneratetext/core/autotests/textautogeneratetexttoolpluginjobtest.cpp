/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetexttoolpluginjobtest.h"
#include "core/tools/textautogeneratetexttoolpluginjob.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateTextToolPluginJobTest)
TextAutoGenerateTextToolPluginJobTest::TextAutoGenerateTextToolPluginJobTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextToolPluginJobTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateTextToolPluginJob w;
    QVERIFY(w.toolArguments().isEmpty());
    QVERIFY(w.requiredArguments().isEmpty());
    // TODO
}

#include "moc_textautogeneratetexttoolpluginjobtest.cpp"
