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

using namespace Qt::Literals::StringLiterals;

QTEST_GUILESS_MAIN(TextAutoGenerateExportChatAsJsonJobTest)

TextAutoGenerateExportChatAsJsonJobTest::TextAutoGenerateExportChatAsJsonJobTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateExportChatAsJsonJobTest::shouldEmitExportDoneOnSuccess()
{
    QTemporaryDir dir;
    QVERIFY(dir.isValid());
    const QString fileName = dir.filePath(u"export.json"_s);

    TextAutoGenerateText::TextAutoGenerateMessage message;
    message.setUuid("msg-1");
    message.setSender(TextAutoGenerateText::TextAutoGenerateMessage::Sender::User);
    message.setContent(u"hello"_s);

    auto job = new TextAutoGenerateText::TextAutoGenerateExportChatAsJsonJob(this);
    TextAutoGenerateText::TextAutoGenerateExportChatBaseJob::ExportChatInfo info;
    info.filename = fileName;
    info.chatTitle = u"title"_s;
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
    QCOMPARE(obj.value(u"title"_s).toString(), u"title"_s);
    QCOMPARE(obj.value(u"messages"_s).toArray().size(), 1);
}

void TextAutoGenerateExportChatAsJsonJobTest::shouldNotEmitExportDoneWhenWriteFails()
{
    if (!QFile::exists(u"/dev/full"_s)) {
        QSKIP("/dev/full is not available on this platform");
    }

    TextAutoGenerateText::TextAutoGenerateMessage message;
    message.setUuid("msg-1");
    message.setSender(TextAutoGenerateText::TextAutoGenerateMessage::Sender::User);
    message.setContent(u"hello"_s);

    auto job = new TextAutoGenerateText::TextAutoGenerateExportChatAsJsonJob(this);
    TextAutoGenerateText::TextAutoGenerateExportChatBaseJob::ExportChatInfo info;
    info.filename = u"/dev/full"_s;
    info.chatTitle = u"title"_s;
    info.listMessages.append(message);
    job->setInfo(info);

    QSignalSpy spy(job, &TextAutoGenerateText::TextAutoGenerateExportChatBaseJob::exportDone);
    job->start();

    QCOMPARE(spy.count(), 0);
}

#include "moc_textautogenerateexportchatasjsonjobtest.cpp"
