/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratechattest.h"

#include "core/textautogeneratechat.h"
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateChatTest)

using namespace Qt::Literals::StringLiterals;
TextAutoGenerateChatTest::TextAutoGenerateChatTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateChatTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateChat w;
    QVERIFY(!w.favorite());
    QVERIFY(!w.archived());
    QVERIFY(w.title().isEmpty());
    QVERIFY(w.identifier().isEmpty());
    QVERIFY(w.prompt().isEmpty());

    // 10/05/2025 => size 72
    QCOMPARE(sizeof(TextAutoGenerateText::TextAutoGenerateChat), 104);
}

void TextAutoGenerateChatTest::shouldSerializeDeserialize()
{
    {
        TextAutoGenerateText::TextAutoGenerateChat w;
        w.setArchived(false);
        w.setFavorite(true);
        w.setTitle(u"bla"_s);
        w.setIdentifier("foo");

        const QByteArray ba = w.serialize(w, false);
        const QJsonDocument doc = QJsonDocument::fromJson(ba);
        TextAutoGenerateText::TextAutoGenerateChat ba1 = TextAutoGenerateText::TextAutoGenerateChat::deserialize(doc.object());
        QCOMPARE(w, ba1);
    }

    {
        TextAutoGenerateText::TextAutoGenerateChat w;
        w.setArchived(true);
        w.setFavorite(false);
        w.setTitle(u"bla2"_s);
        w.setIdentifier("foo3");

        const QByteArray ba = w.serialize(w, false);
        const QJsonDocument doc = QJsonDocument::fromJson(ba);
        TextAutoGenerateText::TextAutoGenerateChat ba1 = TextAutoGenerateText::TextAutoGenerateChat::deserialize(doc.object());
        QCOMPARE(w, ba1);
    }
}

void TextAutoGenerateChatTest::shouldClassifySectionHistory()
{
    TextAutoGenerateText::TextAutoGenerateChat chat;

    chat.setDateTime(QDateTime(QDate::currentDate(), QTime(12, 0)).toSecsSinceEpoch());
    QCOMPARE(chat.section(), TextAutoGenerateText::TextAutoGenerateChat::SectionHistory::Today);

    chat.setDateTime(QDateTime(QDate::currentDate().addDays(-3), QTime(12, 0)).toSecsSinceEpoch());
    QCOMPARE(chat.section(), TextAutoGenerateText::TextAutoGenerateChat::SectionHistory::LessThanSevenDays);

    chat.setDateTime(QDateTime(QDate::currentDate().addDays(-10), QTime(12, 0)).toSecsSinceEpoch());
    QCOMPARE(chat.section(), TextAutoGenerateText::TextAutoGenerateChat::SectionHistory::LessThanThirtyDays);

    chat.setDateTime(QDateTime(QDate::currentDate().addDays(-45), QTime(12, 0)).toSecsSinceEpoch());
    QCOMPARE(chat.section(), TextAutoGenerateText::TextAutoGenerateChat::SectionHistory::Later);

    // Compatibility with millisecond timestamps.
    chat.setDateTime(QDateTime(QDate::currentDate().addDays(-2), QTime(12, 0)).toMSecsSinceEpoch());
    QCOMPARE(chat.section(), TextAutoGenerateText::TextAutoGenerateChat::SectionHistory::LessThanSevenDays);
}

#include "moc_textautogeneratechattest.cpp"
