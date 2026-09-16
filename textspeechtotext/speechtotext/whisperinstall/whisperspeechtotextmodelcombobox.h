/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "speechtotextwhisperinstall_export.h"
#include "whisperspeechtotextmodelsjob.h"
#include <QComboBox>

/*!
 * \brief Lets the user pick the whisper model to transcribe with.
 *
 * The models are the ones whisper_helper.py reports: their list is not built in
 * here, so a model added to the script shows up without a new release. The
 * listing needs neither the virtualenv nor faster-whisper, which is what makes
 * it possible to choose a model before installing whisper.
 */
class SPEECHTOTEXTWHISPERINSTALL_EXPORT WhisperSpeechToTextModelComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit WhisperSpeechToTextModelComboBox(QWidget *parent = nullptr);
    ~WhisperSpeechToTextModelComboBox() override;

    /*! Asks the script for the models, and fills the box when it answers. */
    void fill();

    /*! Fills the box with \a models, for a caller which already has them. */
    void setModels(const WhisperSpeechToTextModelsJob::ModelInfos &models);

    /*! Asks again which models are on disk, after one was downloaded. */
    void refreshCachedModels();

    /*! Marks the models of \a identifiers as being on disk already. */
    void setCachedModels(const QStringList &identifiers);
    [[nodiscard]] QStringList cachedModels() const;

    /*!
     * Whether the cache was looked at. An empty cachedModels() says nothing by
     * itself: it is also what a listing which could not run leaves behind.
     */
    [[nodiscard]] bool cachedModelsKnown() const;

    /*! Whether \a identifier is on disk, so using it costs no download. */
    [[nodiscard]] bool isModelDownloaded(const QString &identifier) const;

    [[nodiscard]] QString currentModel() const;

    /*!
     * Selects \a identifier, or the model the script defaults to when it is
     * empty or unknown. Calling it while the listing is running is what a caller
     * loading its settings does: the selection is applied once the models are in.
     */
    void setCurrentModel(const QString &identifier);

Q_SIGNALS:
    void currentModelChanged(const QString &identifier);
    void modelsLoaded();
    void modelsFailed();
    /*! The models on disk are known: what they cost can be shown. */
    void cachedModelsLoaded();

private:
    SPEECHTOTEXTWHISPERINSTALL_NO_EXPORT void slotCurrentIndexChanged();
    SPEECHTOTEXTWHISPERINSTALL_NO_EXPORT void updateItems();

    WhisperSpeechToTextModelsJob::ModelInfos mModels;
    QStringList mCachedModels;
    bool mCachedModelsKnown = false;
    QString mPendingModel;
    QString mDefaultModel;
    bool mFilling = false;
};
