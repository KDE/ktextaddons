/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechkokorodownloadvoicejob.h"
#include "texttospeech_kokoroinstall_lib_debug.h"
#include "texttospeechkokoroutils.h"

#include <KLocalizedString>
#include <QJsonDocument>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextEditTextToSpeech;
TextToSpeechKokoroDownloadVoiceJob::TextToSpeechKokoroDownloadVoiceJob(QObject *parent)
    : QObject{parent}
{
}

TextToSpeechKokoroDownloadVoiceJob::~TextToSpeechKokoroDownloadVoiceJob() = default;

void TextToSpeechKokoroDownloadVoiceJob::setVoices(const QStringList &voiceIdentifiers)
{
    mVoiceIdentifiers = voiceIdentifiers;
}

bool TextToSpeechKokoroDownloadVoiceJob::downloadModel() const
{
    return mDownloadModel;
}

void TextToSpeechKokoroDownloadVoiceJob::setDownloadModel(bool newDownloadModel)
{
    mDownloadModel = newDownloadModel;
}

bool TextToSpeechKokoroDownloadVoiceJob::canStart() const
{
    return !mVoiceIdentifiers.isEmpty() && !TextToSpeechKokoroUtils::pythonScriptPath().isEmpty() && !TextToSpeechKokoroUtils::venvPython().isEmpty();
}

void TextToSpeechKokoroDownloadVoiceJob::start()
{
    if (!canStart()) {
        failed(u"Impossible to start TextToSpeechKokoroDownloadVoiceJob"_s);
        return;
    }

    mProcess = new QProcess(this);
    connect(mProcess, &QProcess::readyReadStandardOutput, this, &TextToSpeechKokoroDownloadVoiceJob::slotReadyReadStandardOutput);
    connect(mProcess, &QProcess::finished, this, &TextToSpeechKokoroDownloadVoiceJob::slotFinished);
    connect(mProcess, &QProcess::errorOccurred, this, [this](QProcess::ProcessError error) {
        // finished() is not emitted when the process could not be started at all.
        if (error == QProcess::FailedToStart) {
            failed(u"Unable to start "_s + mProcess->program());
        }
    });

    QStringList arguments{TextToSpeechKokoroUtils::pythonScriptPath(), u"download"_s, u"--json"_s};
    if (mDownloadModel) {
        arguments << u"model"_s;
    }
    arguments += mVoiceIdentifiers;
    mProcess->start(TextToSpeechKokoroUtils::venvPython(), arguments);
}

void TextToSpeechKokoroDownloadVoiceJob::slotReadyReadStandardOutput()
{
    mPendingOutput += mProcess->readAllStandardOutput();
    for (qsizetype end = mPendingOutput.indexOf('\n'); end != -1; end = mPendingOutput.indexOf('\n')) {
        parseEvent(mPendingOutput.left(end));
        mPendingOutput.remove(0, end + 1);
    }
}

void TextToSpeechKokoroDownloadVoiceJob::parseEvent(const QByteArray &line)
{
    const QJsonObject event = QJsonDocument::fromJson(line).object();
    if (event.isEmpty()) {
        return;
    }
    const QString type = event.value("type"_L1).toString();
    if (type == "finished"_L1) {
        return;
    }
    const QString file = event.value("file"_L1).toString();
    if (type == "downloading"_L1) {
        Q_EMIT downloadMessage(i18n("Downloading %1…", file));
        return;
    }
    Q_EMIT downloadProgress(event.value("index"_L1).toInt(), event.value("total"_L1).toInt());
    if (type == "error"_L1) {
        const QString message = event.value("message"_L1).toString();
        qCWarning(KOKORO_INSTALL_TEXT_TO_SPEECH_LIB_LOG) << "Unable to download" << file << message;
        Q_EMIT downloadMessage(i18n("Unable to download %1: %2", file, message));
    }
}

void TextToSpeechKokoroDownloadVoiceJob::slotFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    slotReadyReadStandardOutput();
    mPendingOutput.clear();
    if (exitStatus != QProcess::NormalExit || exitCode != 0) {
        failed(u"Unable to download voices "_s + mVoiceIdentifiers.join(u' ') + u". Exit code: "_s + QString::number(exitCode));
        return;
    }
    Q_EMIT downloadVoicesDone();
    deleteLater();
}

void TextToSpeechKokoroDownloadVoiceJob::failed(const QString &errorMessage)
{
    qCWarning(KOKORO_INSTALL_TEXT_TO_SPEECH_LIB_LOG) << errorMessage;
    Q_EMIT downloadVoicesFailed();
    deleteLater();
}

#include "moc_texttospeechkokorodownloadvoicejob.cpp"
