/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QProcess>
#include <QStringList>
namespace TextEditTextToSpeech
{
class TextToSpeechKokoroDownloadVoiceJob : public QObject
{
    Q_OBJECT
public:
    explicit TextToSpeechKokoroDownloadVoiceJob(QObject *parent = nullptr);
    ~TextToSpeechKokoroDownloadVoiceJob() override;

    void setVoices(const QStringList &voiceIdentifiers);

    [[nodiscard]] bool downloadModel() const;
    void setDownloadModel(bool newDownloadModel);

    [[nodiscard]] bool canStart() const;

    void start();

Q_SIGNALS:
    void downloadVoicesDone();
    void downloadVoicesFailed();
    void downloadProgress(int index, int total);
    void downloadMessage(const QString &message);

private:
    void slotReadyReadStandardOutput();
    void slotFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void parseEvent(const QByteArray &line);
    void failed(const QString &errorMessage);

    QStringList mVoiceIdentifiers;
    QByteArray mPendingOutput;
    QProcess *mProcess = nullptr;
    bool mDownloadModel = true;
};
}
