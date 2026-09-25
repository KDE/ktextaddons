/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratemanagertest.h"
#include "core/models/textautogeneratechatsmodel.h"
#include "core/textautogeneratemanager.h"
#include <QSignalSpy>
#include <QStandardPaths>
#include <QTest>

using namespace Qt::Literals::StringLiterals;

QTEST_GUILESS_MAIN(TextAutoGenerateManagerTest)

TextAutoGenerateManagerTest::TextAutoGenerateManagerTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutoGenerateManagerTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateManager w;
    QVERIFY(w.currentChatId().isEmpty());
    QVERIFY(w.textAutoGenerateChatsModel());
    QVERIFY(!w.showArchived());
    QVERIFY(!w.debug());
}

void TextAutoGenerateManagerTest::shouldIsFavorite()
{
    const TextAutoGenerateText::TextAutoGenerateManager w;
    QVERIFY(!w.chatIsFavorite({}));
}

void TextAutoGenerateManagerTest::shouldSetDebug()
{
    qputenv("TEXTAUTOGENERATE_DEBUGGING", "1");
    const TextAutoGenerateText::TextAutoGenerateManager w;
    QVERIFY(w.debug());
}

void TextAutoGenerateManagerTest::shouldEmitCurrentChatIdChangedWhenReset()
{
    TextAutoGenerateText::TextAutoGenerateManager w;
    const QSignalSpy spy(&w, &TextAutoGenerateText::TextAutoGenerateManager::currentChatIdChanged);

    w.setCurrentChatId("chat-1");
    QCOMPARE(spy.count(), 1);
    QCOMPARE(w.currentChatId(), "chat-1"_ba);

    w.resetCurrentChatId();
    QCOMPARE(spy.count(), 2);
    QVERIFY(w.currentChatId().isEmpty());
}
void TextAutoGenerateManagerTest::shouldCreateEphemeralChatWithoutChangingCurrentChat()
{
    TextAutoGenerateText::TextAutoGenerateManager w;
    w.setCurrentChatId("chat-1");
    const QSignalSpy spy(&w, &TextAutoGenerateText::TextAutoGenerateManager::currentChatIdChanged);

    const QByteArray chatId = w.createEphemeralChat();
    QVERIFY(!chatId.isEmpty());
    // The current chat (main window) is not changed
    QCOMPARE(w.currentChatId(), "chat-1"_ba);
    QCOMPARE(spy.count(), 0);

    const TextAutoGenerateText::TextAutoGenerateChat chat = w.textAutoGenerateChatsModel()->chat(chatId);
    QCOMPARE(chat.identifier(), chatId);
    QCOMPARE(chat.persistence(), TextAutoGenerateText::TextAutoGenerateChat::Persistence::Ephemeral);
    QVERIFY(w.messagesModelFromChatId(chatId));
    QVERIFY(w.textAutoGenerateChatsModel()->isInitialized(chatId));

    w.removeDiscussion(chatId);
    QVERIFY(w.textAutoGenerateChatsModel()->chat(chatId).identifier().isEmpty());
}

void TextAutoGenerateManagerTest::shouldResetCurrentChatIdWhenRemovingCurrentChat()
{
    TextAutoGenerateText::TextAutoGenerateManager w;
    const QByteArray chatId = w.createEphemeralChat();
    w.setCurrentChatId(chatId);
    const QSignalSpy spy(&w, &TextAutoGenerateText::TextAutoGenerateManager::currentChatIdChanged);

    w.removeDiscussion(chatId);
    QVERIFY(w.currentChatId().isEmpty());
    QCOMPARE(spy.count(), 1);
    QVERIFY(w.textAutoGenerateChatsModel()->chat(chatId).identifier().isEmpty());
}

void TextAutoGenerateManagerTest::shouldKeepCurrentChatIdWhenRemovingAnotherChat()
{
    TextAutoGenerateText::TextAutoGenerateManager w;
    const QByteArray currentChatId = w.createEphemeralChat();
    const QByteArray otherChatId = w.createEphemeralChat();
    w.setCurrentChatId(currentChatId);
    const QSignalSpy spy(&w, &TextAutoGenerateText::TextAutoGenerateManager::currentChatIdChanged);

    w.removeDiscussion(otherChatId);
    QCOMPARE(w.currentChatId(), currentChatId);
    QCOMPARE(spy.count(), 0);
    QVERIFY(w.textAutoGenerateChatsModel()->chat(otherChatId).identifier().isEmpty());
    QCOMPARE(w.textAutoGenerateChatsModel()->chat(currentChatId).identifier(), currentChatId);
}

#include "moc_textautogeneratemanagertest.cpp"
