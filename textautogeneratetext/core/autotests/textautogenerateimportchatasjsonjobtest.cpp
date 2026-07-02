/*
 * SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "textautogenerateimportchatasjsonjobtest.h"

#include <QSignalSpy>
#include <QTemporaryDir>
#include <QTest>

#include <TextAutoGenerateText/TextAutoGenerateImportChatAsJsonJob>

QTEST_GUILESS_MAIN(TextAutoGenerateImportChatAsJsonJobTest)

TextAutoGenerateImportChatAsJsonJobTest::TextAutoGenerateImportChatAsJsonJobTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateImportChatAsJsonJobTest::shouldRemapMessageAndAnswerUuids()
{
    QTemporaryDir dir;
    QVERIFY(dir.isValid());

    const QString fileName = dir.filePath(QStringLiteral("import.json"));
    QFile f(fileName);
    QVERIFY(f.open(QIODevice::WriteOnly));
    f.write(R"({
"title":"chat",
"messages":[
  {"identifier":"id-a","text":"user","sender":"user","dateTime":1},
  {"identifier":"id-b","answerIdentifier":"id-a","text":"assistant","sender":"llm","dateTime":2}
]
})");
    f.close();

    auto job = new TextAutoGenerateText::TextAutoGenerateImportChatAsJsonJob(this);
    TextAutoGenerateText::TextAutoGenerateImportChatBaseJob::ImportChatInfo info;
    info.filename = fileName;
    job->setInfo(info);

    QSignalSpy spy(job, &TextAutoGenerateText::TextAutoGenerateImportChatBaseJob::importDone);
    job->start();

    QCOMPARE(spy.count(), 1);
    const QList<QVariant> args = spy.takeFirst();
    QCOMPARE(args.at(0).toString(), QStringLiteral("chat"));

    const QList<TextAutoGenerateText::TextAutoGenerateMessage> importedMessages =
        qvariant_cast<QList<TextAutoGenerateText::TextAutoGenerateMessage>>(args.at(1));
    QCOMPARE(importedMessages.size(), 2);

    const TextAutoGenerateText::TextAutoGenerateMessage &first = importedMessages.at(0);
    const TextAutoGenerateText::TextAutoGenerateMessage &second = importedMessages.at(1);

    QVERIFY(!first.uuid().isEmpty());
    QVERIFY(!second.uuid().isEmpty());
    QVERIFY(first.uuid() != "id-a");
    QVERIFY(second.uuid() != "id-b");
    QCOMPARE(second.answerUuid(), first.uuid());
}

#include "moc_textautogenerateimportchatasjsonjobtest.cpp"
