/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextplugintest.h"
#include "core/textautogeneratetextplugin.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateTextPluginTest)
TextAutoGenerateTextPluginTest::TextAutoGenerateTextPluginTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextPluginTest::shouldSendToLLMInfoDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateTextPlugin::SendToAssistantInfo info;
    QVERIFY(info.chatId.isEmpty());
    QVERIFY(info.message.isEmpty());
    QVERIFY(info.messageUuid.isEmpty());
}

#include "moc_textautogeneratetextplugintest.cpp"
