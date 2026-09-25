/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratelocaldatabasemanagertest.h"
#include "core/localdatabase/textautogeneratelocaldatabasemanager.h"
#include <QStandardPaths>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(TextAutoGenerateLocalDatabaseManagerTest)
TextAutoGenerateLocalDatabaseManagerTest::TextAutoGenerateLocalDatabaseManagerTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutoGenerateLocalDatabaseManagerTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateLocalDatabaseManager w;
    QVERIFY(w.ephemeralChatIds().isEmpty());
    QVERIFY(w.chatsList().isEmpty());
}

void TextAutoGenerateLocalDatabaseManagerTest::shouldAddRemoveEphemeral()
{
    TextAutoGenerateText::TextAutoGenerateLocalDatabaseManager w;
    w.addEphemeralChat("test1"_ba);

    QVERIFY(!w.ephemeralChatIds().isEmpty());
    QCOMPARE(w.ephemeralChatIds().count(), 1);

    w.addEphemeralChat("test1"_ba);
    QCOMPARE(w.ephemeralChatIds().count(), 1);

    w.removeEphemeralChat("test1"_ba);
    QVERIFY(w.ephemeralChatIds().isEmpty());

    w.addEphemeralChat("test2"_ba);
    QCOMPARE(w.ephemeralChatIds().count(), 1);
    w.removeEphemeralChat("test1"_ba);
    QCOMPARE(w.ephemeralChatIds().count(), 1);
    w.removeEphemeralChat("test2"_ba);
    QVERIFY(w.ephemeralChatIds().isEmpty());
}

#include "moc_textautogeneratelocaldatabasemanagertest.cpp"
