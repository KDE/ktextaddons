/*
 * SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "textautogenerateexportchatasjsonjobtest.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSignalSpy>
#include <QTemporaryDir>
#include <QTest>
#include <TextAutoGenerateText/TextAutoGenerateExportChatAsJsonJob>
#include <TextAutoGenerateText/TextAutoGenerateMessage>

QTEST_GUILESS_MAIN(TextAutoGenerateExportChatAsJsonJobTest)

TextAutoGenerateExportChatAsJsonJobTest::TextAutoGenerateExportChatAsJsonJobTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateExportChatAsJsonJobTest::shouldEmitExportDoneOnSuccess()
{
    QTemporaryDir dir;
    QVERIFY(dir.isValid());
    const QString fileName = dir.filePath(QStringLiteral("export.json"));

    TextAutoGenerateText::TextAutoGenerateMessage message;
    message.setUuid("msg-1");
    message.setSender(TextAutoGenerateText::TextAutoGenerateMessage::Sender::User);
    message.setContent(QStringLiteral("hello"));

    auto *job = new TextAutoGenerateText::TextAutoGenerateExportChatAsJsonJob(this);
    TextAutoGenerateText::TextAutoGenerateExportChatBaseJob::ExportChatInfo info;
    info.filename = fileName;
    info.chatTitle = QStringLiteral("title");
    info.listMessages.append(message);
    job->setInfo(info);

    QSignalSpy spy(job, &TextAutoGenerateText::TextAutoGenerateExportChatBaseJob::exportDone);
    job->start();

    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toString(), fileName);

    QFile f(fileName);
    QVERIFY(f.open(QIODevice::ReadOnly));
    const QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    QVERIFY(doc.isObject());
    const QJsonObject obj = doc.object();
    QCOMPARE(obj.value(QStringLiteral("title")).toString(), QStringLiteral("title"));
    QCOMPARE(obj.value(QStringLiteral("messages")).toArray().size(), 1);
}

void TextAutoGenerateExportChatAsJsonJobTest::shouldNotEmitExportDoneWhenWriteFails()
{
    if (!QFile::exists(QStringLiteral("/dev/full"))) {
        QSKIP("/dev/full is not available on this platform");
    }

    TextAutoGenerateText::TextAutoGenerateMessage message;
    message.setUuid("msg-1");
    message.setSender(TextAutoGenerateText::TextAutoGenerateMessage::Sender::User);
    message.setContent(QStringLiteral("hello"));

    auto *job = new TextAutoGenerateText::TextAutoGenerateExportChatAsJsonJob(this);
    TextAutoGenerateText::TextAutoGenerateExportChatBaseJob::ExportChatInfo info;
    info.filename = QStringLiteral("/dev/full");
    info.chatTitle = QStringLiteral("title");
    info.listMessages.append(message);
    job->setInfo(info);

    QSignalSpy spy(job, &TextAutoGenerateText::TextAutoGenerateExportChatBaseJob::exportDone);
    job->start();

    QCOMPARE(spy.count(), 0);
}
