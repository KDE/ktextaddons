/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "speechtotextwhisperinstall_export.h"
#include <QList>
#include <QObject>
#include <QPointer>
#include <QProcess>
#include <QString>
class QDebug;

/*!
 * \brief Asks whisper_helper.py which models can be transcribed with.
 *
 * The script is run with its "models" subcommand, which prints the json of the
 * table it keeps. That table is static: the subcommand needs neither the
 * virtualenv nor faster-whisper, so the models can be listed before whisper is
 * installed, which is what choosing the one to download needs.
 *
 * The job deletes itself once it has reported the answer.
 */
class SPEECHTOTEXTWHISPERINSTALL_EXPORT WhisperSpeechToTextModelsJob : public QObject
{
    Q_OBJECT
public:
    struct SPEECHTOTEXTWHISPERINSTALL_EXPORT ModelInfo {
        /*! Name faster-whisper loads the model with, for example "small". */
        QString identifier;
        /*! Name shown to the user. */
        QString name;
        /*! Disk footprint of the converted model, so it can be shown before downloading it. */
        int sizeMib = 0;
        /*! An english only model cannot transcribe anything else. */
        bool multilingual = false;
        /*! The one the script transcribes with when nothing was chosen. */
        bool isDefault = false;

        [[nodiscard]] bool isValid() const;
        [[nodiscard]] bool operator==(const ModelInfo &other) const;
    };
    using ModelInfos = QList<ModelInfo>;

    explicit WhisperSpeechToTextModelsJob(QObject *parent = nullptr);
    ~WhisperSpeechToTextModelsJob() override;

    [[nodiscard]] bool canStart() const;
    void start();

    /*! Parses the json printed by "whisper_helper.py models". */
    [[nodiscard]] static ModelInfos parseModels(const QByteArray &json);

    /*! Same listing, for the callers which cannot wait for a signal. */
    [[nodiscard]] static ModelInfos modelsSynchronously(int timeoutMs = 30000);

    /*! The model the script uses when none was chosen, empty when \a models has none. */
    [[nodiscard]] static QString defaultModel(const ModelInfos &models);

Q_SIGNALS:
    void modelsLoaded(const WhisperSpeechToTextModelsJob::ModelInfos &models);
    void modelsFailed();

private:
    // The process deletes itself as soon as it has answered, which can be long
    // before the job is destroyed with the widget which asked for the listing.
    QPointer<QProcess> mProcess;
};

Q_DECLARE_TYPEINFO(WhisperSpeechToTextModelsJob::ModelInfo, Q_RELOCATABLE_TYPE);
Q_DECLARE_METATYPE(WhisperSpeechToTextModelsJob::ModelInfo)
SPEECHTOTEXTWHISPERINSTALL_EXPORT QDebug operator<<(QDebug d, const WhisperSpeechToTextModelsJob::ModelInfo &t);
