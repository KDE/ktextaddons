/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "speechtotextwhisperinstall_export.h"
#include <QObject>
#include <QProcess>

/*!
 * \brief Downloads a whisper model, reporting how far it got.
 *
 * WhisperModel() fetches what it needs by itself, but it does so in the middle
 * of the first transcription and says nothing while it goes, which for the
 * default model means several hundred megabytes during which the engine looks
 * hung. The job asks whisper_helper.py for the same download on its own: the
 * script reports one json line per event, which is what feeds downloadProgress().
 *
 * The job deletes itself once it has reported the outcome.
 */
class SPEECHTOTEXTWHISPERINSTALL_EXPORT WhisperSpeechToTextDownloadModelJob : public QObject
{
    Q_OBJECT
public:
    /*! One line of what "whisper_helper.py download" prints. */
    struct SPEECHTOTEXTWHISPERINSTALL_EXPORT DownloadEvent {
        /*! "start", "progress", "cached", "missing", "finished" or "error". */
        QString type;
        QString model;
        /*! What went wrong, for an "error" event. */
        QString message;
        /*! Where the model landed, for "cached" and "finished". */
        QString path;
        qint64 received = 0;
        qint64 total = 0;
        /*! Only a "progress" event has one, hence -1 elsewhere. */
        int percent = -1;

        [[nodiscard]] bool isValid() const;
    };

    explicit WhisperSpeechToTextDownloadModelJob(QObject *parent = nullptr);
    ~WhisperSpeechToTextDownloadModelJob() override;

    [[nodiscard]] QString model() const;
    void setModel(const QString &model);

    /*! The model was already in the cache: nothing was downloaded. */
    [[nodiscard]] bool wasCached() const;

    [[nodiscard]] bool canStart() const;
    void start();

    /*! Parses one json line printed by "whisper_helper.py download". */
    [[nodiscard]] static DownloadEvent parseEvent(const QByteArray &line);

Q_SIGNALS:
    void downloadModelDone();
    void downloadModelFailed();
    /*!
     * How far the download got. \a received and \a total are bytes, and they are
     * what a label shows: \a percent never reaches 100, downloadModelDone() is
     * what says that it is over.
     */
    void downloadProgress(int percent, qint64 received, qint64 total);
    void downloadMessage(const QString &message);

private:
    SPEECHTOTEXTWHISPERINSTALL_NO_EXPORT void slotReadyReadStandardOutput();
    SPEECHTOTEXTWHISPERINSTALL_NO_EXPORT void slotFinished(int exitCode, QProcess::ExitStatus exitStatus);
    SPEECHTOTEXTWHISPERINSTALL_NO_EXPORT void processEvent(const DownloadEvent &event);
    SPEECHTOTEXTWHISPERINSTALL_NO_EXPORT void failed(const QString &errorMessage);

    QString mModel;
    QByteArray mPendingOutput;
    QProcess *mProcess = nullptr;
    bool mWasCached = false;
};
Q_DECLARE_TYPEINFO(WhisperSpeechToTextDownloadModelJob::DownloadEvent, Q_RELOCATABLE_TYPE);
