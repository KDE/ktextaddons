/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratechatsmodeltest.h"
#include "core/models/textautogeneratechatsmodel.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateChatsModelTest)
using namespace Qt::Literals::StringLiterals;
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

void TextAutoGenerateChatsModelTest::shouldCheckHasAtLeastOneNotArchivedChat()
{
    TextAutoGenerateText::TextAutoGenerateChatsModel model;
    {
        TextAutoGenerateText::TextAutoGenerateChat chat;
        chat.setIdentifier("foo"_ba);
        model.addChat(chat);
        QVERIFY(model.hasAtLeastOneNotArchivedChat());
    }
    model.clear();
    QVERIFY(!model.hasAtLeastOneNotArchivedChat());
    // Only one chat archived
    {
        TextAutoGenerateText::TextAutoGenerateChat chat;
        chat.setIdentifier("foo"_ba);
        chat.setArchived(true);
        model.addChat(chat);
        QVERIFY(!model.hasAtLeastOneNotArchivedChat());
    }
    model.clear();
    {
        TextAutoGenerateText::TextAutoGenerateChat chat;
        chat.setIdentifier("foo"_ba);
        chat.setArchived(true);
        model.addChat(chat);

        TextAutoGenerateText::TextAutoGenerateChat chat2;
        chat2.setIdentifier("foo1"_ba);
        chat2.setArchived(false);
        model.addChat(chat2);

        QVERIFY(model.hasAtLeastOneNotArchivedChat());
    }
}
#include "moc_textautogeneratechatsmodeltest.cpp"
