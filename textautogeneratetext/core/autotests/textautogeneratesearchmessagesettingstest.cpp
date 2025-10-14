/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesearchmessagesettingstest.h"
#include "core/models/textautogeneratemessagesmodel.h"
#include "core/textautogeneratesearchmessagesettings.h"
#include <QSignalSpy>
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateSearchMessageSettingsTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateSearchMessageSettingsTest::TextAutoGenerateSearchMessageSettingsTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateSearchMessageSettingsTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateSearchMessageSettings w(nullptr);
    QCOMPARE(w.currentSearchIndex(), -1);
    QCOMPARE(w.numberOfSearchReference(), -1);
    QVERIFY(w.currentMessageIdentifier().isEmpty());
}

void TextAutoGenerateSearchMessageSettingsTest::shouldClear()
{
    TextAutoGenerateText::TextAutoGenerateSearchMessageSettings w(nullptr);
    const QByteArray ba = "foo"_ba;
    w.setCurrentMessageIdentifier(ba);
    QCOMPARE(w.currentMessageIdentifier(), ba);

    const int nbSearch = 15;
    w.setNumberOfSearchReference(nbSearch);
    QCOMPARE(w.numberOfSearchReference(), nbSearch);

    const int currentSearchIndex = 45;
    w.setCurrentSearchIndex(currentSearchIndex);
    QCOMPARE(w.currentSearchIndex(), currentSearchIndex);

    w.clear();
    QCOMPARE(w.currentSearchIndex(), -1);
    QCOMPARE(w.numberOfSearchReference(), -1);
    QVERIFY(w.currentMessageIdentifier().isEmpty());
}

void TextAutoGenerateSearchMessageSettingsTest::shouldTestNextSearchStringIndex()
{
    TextAutoGenerateText::TextAutoGenerateMessagesModel model;
    QList<TextAutoGenerateText::TextAutoGenerateMessage> messages;
    {
        TextAutoGenerateText::TextAutoGenerateMessage msg;
        msg.setUuid("foo1"_ba);
        msg.setContent(u"kde and kde"_s);
        msg.setSender(TextAutoGenerateText::TextAutoGenerateMessage::Sender::User);
        msg.generateHtml();
        messages.append(msg);
    }
    {
        TextAutoGenerateText::TextAutoGenerateMessage msg;
        msg.setUuid("foo2"_ba);
        msg.setContent(u"bla bla"_s);
        msg.setSender(TextAutoGenerateText::TextAutoGenerateMessage::Sender::User);
        msg.generateHtml();
        messages.append(msg);
    }
    {
        TextAutoGenerateText::TextAutoGenerateMessage msg;
        msg.setUuid("foo3"_ba);
        msg.setContent(u"kde"_s);
        msg.setSender(TextAutoGenerateText::TextAutoGenerateMessage::Sender::User);
        msg.generateHtml();
        messages.append(msg);
    }
    model.setMessages(messages);
    const int nbSearchString = model.setSearchText(u"kde"_s);
    TextAutoGenerateText::TextAutoGenerateSearchMessageSettings messageSettings(&model);
    messageSettings.setNumberOfSearchReference(nbSearchString);

    QCOMPARE(nbSearchString, 3);
    messageSettings.next();
    // Last one
    QCOMPARE(messageSettings.currentMessageIdentifier(), "foo3"_ba);
    QCOMPARE(messageSettings.currentSearchIndex(), 0);

    messageSettings.next();
    // No other message
    QCOMPARE(messageSettings.currentMessageIdentifier(), ""_ba);
    QCOMPARE(messageSettings.currentSearchIndex(), -1);
}

void TextAutoGenerateSearchMessageSettingsTest::shouldTestPreviousSearchStringIndex()
{
    TextAutoGenerateText::TextAutoGenerateMessagesModel model;
    QList<TextAutoGenerateText::TextAutoGenerateMessage> messages;
    {
        TextAutoGenerateText::TextAutoGenerateMessage msg;
        msg.setUuid("foo1"_ba);
        msg.setContent(u"kde and kde"_s);
        msg.setSender(TextAutoGenerateText::TextAutoGenerateMessage::Sender::User);
        msg.generateHtml();
        messages.append(msg);
    }
    {
        TextAutoGenerateText::TextAutoGenerateMessage msg;
        msg.setUuid("foo2"_ba);
        msg.setContent(u"bla bla"_s);
        msg.setSender(TextAutoGenerateText::TextAutoGenerateMessage::Sender::User);
        msg.generateHtml();
        messages.append(msg);
    }
    {
        TextAutoGenerateText::TextAutoGenerateMessage msg;
        msg.setUuid("foo3"_ba);
        msg.setContent(u"kde"_s);
        msg.setSender(TextAutoGenerateText::TextAutoGenerateMessage::Sender::User);
        msg.generateHtml();
        messages.append(msg);
    }
    model.setMessages(messages);
    const int nbSearchString = model.setSearchText(u"kde"_s);
    TextAutoGenerateText::TextAutoGenerateSearchMessageSettings messageSettings(&model);
    messageSettings.setNumberOfSearchReference(nbSearchString);

    QCOMPARE(nbSearchString, 3);
    messageSettings.previous();
    // Last one
    QCOMPARE(messageSettings.currentMessageIdentifier(), "foo3"_ba);
    QCOMPARE(messageSettings.currentSearchIndex(), 0);

    messageSettings.previous();
    QCOMPARE(messageSettings.currentMessageIdentifier(), "foo1"_ba);
    QCOMPARE(messageSettings.currentSearchIndex(), 1);

    messageSettings.previous();
    QCOMPARE(messageSettings.currentMessageIdentifier(), "foo1"_ba);
    QCOMPARE(messageSettings.currentSearchIndex(), 0);

    // no other search element
    messageSettings.previous();
    QCOMPARE(messageSettings.currentMessageIdentifier(), ""_ba);
    QCOMPARE(messageSettings.currentSearchIndex(), -1);
}

#include "moc_textautogeneratesearchmessagesettingstest.cpp"
