/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratechatsettingstest.h"
#include "core/textautogeneratechatsettings.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateChatSettingsTest)
TextAutoGenerateChatSettingsTest::TextAutoGenerateChatSettingsTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateChatSettingsTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateChatSettings::PendingTypedInfo info;
    QVERIFY(info.text.isEmpty());
    QCOMPARE(info.scrollbarPosition, -1);
    QVERIFY(!info.isValid());
}
