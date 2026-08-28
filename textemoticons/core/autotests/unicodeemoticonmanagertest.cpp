/*
   SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "unicodeemoticonmanagertest.h"
#include "unicodeemoticonmanager.h"
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(UnicodeEmoticonManagerTest)

UnicodeEmoticonManagerTest::UnicodeEmoticonManagerTest(QObject *parent)
    : QObject{parent}
{
}

void UnicodeEmoticonManagerTest::shouldHaveDefaultValues()
{
    TextEmoticonsCore::UnicodeEmoticonManager w;
    QVERIFY(!w.unicodeEmojiList().isEmpty());
    QVERIFY(!w.categories().isEmpty());
}

void UnicodeEmoticonManagerTest::shouldFindEmoji_data()
{
    QTest::addColumn<QString>("searched");
    QTest::addColumn<QString>("unicode");

    // The identifiers come from emojibase, and so do the names other clients send us.
    QTest::newRow("identifier") << u":party:"_s << u"\U0001F389"_s;
    QTest::newRow("alias") << u":party_popper:"_s << u"\U0001F389"_s;
    // The names shipped before emojibase must keep resolving, as aliases.
    QTest::newRow("previous-identifier") << u":tada:"_s << u"\U0001F389"_s;
    QTest::newRow("previous-ascii") << u"<3"_s << u"\u2764\uFE0F"_s;
    // A message that was not written with a shortname carries the emoji itself.
    QTest::newRow("unicode") << u"\U0001F389"_s << u"\U0001F389"_s;
    // Emoji that appeared after the previous emoji set stopped being updated.
    QTest::newRow("melting-face") << u":melt:"_s << u"\U0001FAE0"_s;
    QTest::newRow("skin-tone") << u":thumbsup_tone3:"_s << u"\U0001F44D\U0001F3FD"_s;
    QTest::newRow("mixed-skin-tone") << u":handshake_tone1-2:"_s << u"\U0001FAF1\U0001F3FB\u200D\U0001FAF2\U0001F3FC"_s;
    QTest::newRow("unknown") << u":not-an-emoji:"_s << QString();
}

void UnicodeEmoticonManagerTest::shouldFindEmoji()
{
    QFETCH(QString, searched);
    QFETCH(QString, unicode);
    TextEmoticonsCore::UnicodeEmoticonManager manager;
    QCOMPARE(manager.unicodeEmoticonForEmoji(searched).unicode(), unicode);
}

#include "moc_unicodeemoticonmanagertest.cpp"
