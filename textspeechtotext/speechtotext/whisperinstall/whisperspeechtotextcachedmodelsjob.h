/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "speechtotextwhisperinstall_export.h"
#include <QObject>
#include <QPointer>
#include <QProcess>
#include <QStringList>

/*!
 * \brief Tells which models are already on disk, so the user knows what a
 * selection is going to cost.
 *
 * "whisper_helper.py download --all" answers for every model of the table at
 * once: asking model by model would be one interpreter start for each of them.
 * Nothing is downloaded, only the cache is looked at, but huggingface_hub is
 * what looks at it, so the virtualenv is needed.
 *
 * The job deletes itself once it has reported the answer.
 */
class SPEECHTOTEXTWHISPERINSTALL_EXPORT WhisperSpeechToTextCachedModelsJob : public QObject
{
    Q_OBJECT
public:
    explicit WhisperSpeechToTextCachedModelsJob(QObject *parent = nullptr);
    ~WhisperSpeechToTextCachedModelsJob() override;

    [[nodiscard]] bool canStart() const;
    void start();

    /*! Identifiers of the models the script reported as cached. */
    [[nodiscard]] static QStringList parseCachedModels(const QByteArray &output);

Q_SIGNALS:
    void cachedModelsLoaded(const QStringList &models);
    void cachedModelsFailed();

private:
    QByteArray mPendingOutput;
    // The process deletes itself as soon as it has answered, which can be long
    // before the job is destroyed with the widget which asked for the listing.
    QPointer<QProcess> mProcess;
};
