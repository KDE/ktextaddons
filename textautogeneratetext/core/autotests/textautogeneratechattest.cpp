/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratechattest.h"
using namespace Qt::Literals::StringLiterals;

#include "core/textautogeneratechat.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateChatTest)

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

    // 10/05/2025 => size 72
    QCOMPARE(sizeof(TextAutoGenerateText::TextAutoGenerateChat), 80);
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
        QJsonDocument doc = QJsonDocument::fromJson(ba);
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
        QJsonDocument doc = QJsonDocument::fromJson(ba);
        TextAutoGenerateText::TextAutoGenerateChat ba1 = TextAutoGenerateText::TextAutoGenerateChat::deserialize(doc.object());
        QCOMPARE(w, ba1);
    }
}

#include "moc_textautogeneratechattest.cpp"
