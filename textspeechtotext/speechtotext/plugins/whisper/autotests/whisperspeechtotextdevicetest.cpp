/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextdevicetest.h"
using namespace Qt::Literals::StringLiterals;

#include "whisperspeechtotextdevice.h"
#include "whisperspeechtotextutils.h"
#include <QSignalSpy>
#include <QTest>

QTEST_GUILESS_MAIN(WhisperSpeechToTextDeviceTest)
WhisperSpeechToTextDeviceTest::WhisperSpeechToTextDeviceTest(QObject *parent)
    : QObject{parent}
{
}

void WhisperSpeechToTextDeviceTest::shouldHaveDefaultValues()
{
    WhisperSpeechToTextDevice w;
    // QAudioSource pushes the audio in, so the device has to be open for writing.
    QVERIFY(w.isOpen());
    QVERIFY(w.isWritable());
    QVERIFY(w.isSequential());
    // Nothing was started: there is no script to talk to yet.
    QVERIFY(!w.available());

    const WhisperSpeechToTextDevice::WhisperSpeechToTextDeviceInfo info = w.info();
    QVERIFY(info.model.isEmpty());
    QVERIFY(info.language.isEmpty());
    QVERIFY(info.computeType.isEmpty());
    QVERIFY(info.device.isEmpty());
    QVERIFY(info.prompt.isEmpty());
    QVERIFY(!info.partials);
}

void WhisperSpeechToTextDeviceTest::shouldAssignInfo()
{
    if (!WhisperSpeechToTextUtils::venvPython().isEmpty() && !WhisperSpeechToTextUtils::pythonScriptPath().isEmpty()) {
        QSKIP("whisper is installed here: initialize() would start the script for real.");
    }
    WhisperSpeechToTextDevice w;
    WhisperSpeechToTextDevice::WhisperSpeechToTextDeviceInfo info;
    info.model = u"small"_s;
    info.language = u"fr"_s;
    info.partials = true;
    // Without the virtualenv there is no python to run the script with.
    QVERIFY(!w.initialize(WhisperSpeechToTextDevice::WhisperSpeechToTextDeviceInfo(info)));
    // The settings are kept even when the script could not be started: the next
    // dictation is the one which hands them over.
    QCOMPARE(w.info().model, info.model);
    QCOMPARE(w.info().language, info.language);
    QCOMPARE(w.info().partials, info.partials);
}

void WhisperSpeechToTextDeviceTest::shouldTakeCompleteFramesOnly()
{
    QByteArray buffer;
    QVERIFY(WhisperSpeechToTextDevice::takeFrames(buffer).isEmpty());
    QVERIFY(buffer.isEmpty());

    // A frame is only complete once its line ends.
    const QByteArray line = R"({"type":"final","id":1,"text":"bonjour"})";
    buffer = line;
    QVERIFY(WhisperSpeechToTextDevice::takeFrames(buffer).isEmpty());
    QCOMPARE(buffer, line);

    buffer += "\n";
    const QList<QJsonObject> frames = WhisperSpeechToTextDevice::takeFrames(buffer);
    QCOMPARE(frames.count(), 1);
    QCOMPARE(frames.at(0).value("type"_L1).toString(), u"final"_s);
    QCOMPARE(frames.at(0).value("text"_L1).toString(), u"bonjour"_s);
    QVERIFY(buffer.isEmpty());
}

void WhisperSpeechToTextDeviceTest::shouldTakeSeveralFramesAtOnce()
{
    // One read can bring several frames, and the beginning of one more.
    QByteArray buffer = R"({"type":"started","id":1})"
                        "\n"
                        R"({"type":"final","id":1,"text":"bonjour"})"
                        "\n"
                        R"({"type":"end",)";
    const QList<QJsonObject> frames = WhisperSpeechToTextDevice::takeFrames(buffer);
    QCOMPARE(frames.count(), 2);
    QCOMPARE(frames.at(0).value("type"_L1).toString(), u"started"_s);
    QCOMPARE(frames.at(1).value("type"_L1).toString(), u"final"_s);
    QCOMPARE(buffer, R"({"type":"end",)");

    // What is left is taken with the rest of its line.
    buffer += R"("id":1})"
              "\n";
    const QList<QJsonObject> endFrames = WhisperSpeechToTextDevice::takeFrames(buffer);
    QCOMPARE(endFrames.count(), 1);
    QCOMPARE(endFrames.at(0).value("type"_L1).toString(), u"end"_s);
    QVERIFY(buffer.isEmpty());
}

void WhisperSpeechToTextDeviceTest::shouldSkipTheDeclaredPayload()
{
    // The payload of a frame must not be read as if it were the next line.
    QByteArray buffer = R"({"type":"audio","size":5})"
                        "\n"
                        "a\nb\nc"
                        R"({"type":"end","id":1})"
                        "\n";
    const QList<QJsonObject> frames = WhisperSpeechToTextDevice::takeFrames(buffer);
    QCOMPARE(frames.count(), 2);
    QCOMPARE(frames.at(0).value("type"_L1).toString(), u"audio"_s);
    QCOMPARE(frames.at(1).value("type"_L1).toString(), u"end"_s);
    QVERIFY(buffer.isEmpty());

    // An incomplete payload keeps its own frame waiting.
    const QByteArray truncated = R"({"type":"audio","size":5})"
                                 "\n"
                                 "abc";
    QByteArray incomplete = truncated;
    QVERIFY(WhisperSpeechToTextDevice::takeFrames(incomplete).isEmpty());
    QCOMPARE(incomplete, truncated);
}

void WhisperSpeechToTextDeviceTest::shouldNotSendAudioWithoutBackend()
{
    WhisperSpeechToTextDevice w;
    QSignalSpy resultSpy(&w, &WhisperSpeechToTextDevice::result);
    // The audio is dropped, but QAudioSource must not be told that the device
    // refused it: it would stop the capture.
    const QByteArray audio(1600, 0);
    QCOMPARE(w.write(audio), audio.size());
    // Nothing to flush, and nothing recognized.
    w.finish();
    QCOMPARE(resultSpy.count(), 0);
}

#include "moc_whisperspeechtotextdevicetest.cpp"
