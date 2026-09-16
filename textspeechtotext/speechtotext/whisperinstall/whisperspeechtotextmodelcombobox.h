/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "speechtotextwhisperinstall_export.h"
#include "whisperspeechtotextmodelsjob.h"
#include <QComboBox>

class SPEECHTOTEXTWHISPERINSTALL_EXPORT WhisperSpeechToTextModelComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit WhisperSpeechToTextModelComboBox(QWidget *parent = nullptr);
    ~WhisperSpeechToTextModelComboBox() override;

    void fill();

    void setModels(const WhisperSpeechToTextModelsJob::ModelInfos &models);

    void refreshCachedModels();

    void setCachedModels(const QStringList &identifiers);
    [[nodiscard]] QStringList cachedModels() const;

    [[nodiscard]] bool cachedModelsKnown() const;

    [[nodiscard]] bool isModelDownloaded(const QString &identifier) const;

    [[nodiscard]] QString currentModel() const;

    void setCurrentModel(const QString &identifier);

Q_SIGNALS:
    void currentModelChanged(const QString &identifier);
    void modelsLoaded();
    void modelsFailed();
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
