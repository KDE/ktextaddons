/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratechatsmodeltest.h"
#include "core/models/textautogeneratechatsmodel.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateChatsModelTest)

TextAutoGenerateChatsModelTest::TextAutoGenerateChatsModelTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateChatsModelTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateChatsModel model;
    QVERIFY(model.chats().isEmpty());
    QVERIFY(!model.hasChatInProgress());
    QVERIFY(!model.hasAtLeastOneNotArchivedChat());
    QVERIFY(model.chatsId().isEmpty());
    QVERIFY(!model.textAutoGenerateChatSettings());
}
#include "moc_textautogeneratechatsmodeltest.cpp"
