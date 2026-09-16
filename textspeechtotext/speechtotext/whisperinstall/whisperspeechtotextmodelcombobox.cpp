/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextmodelcombobox.h"
#include "whisperspeechtotextcachedmodelsjob.h"
#include <KLocalizedString>
#include <QLocale>

using namespace Qt::Literals::StringLiterals;

namespace
{
[[nodiscard]] QString modelSize(int sizeMib)
{
    // The table of the script rounds the megabytes anyway, so decimals would say
    // nothing there. Past the gigabyte they are what separates the models: 1530
    // and 3090 MiB both read "3 GiB" otherwise.
    const int precision = sizeMib >= 1024 ? 1 : 0;
    return QLocale().formattedDataSize(qint64{sizeMib} * 1024 * 1024, precision);
}

[[nodiscard]] QString modelLabel(const WhisperSpeechToTextModelsJob::ModelInfo &info, bool cached)
{
    if (cached) {
        return i18nc("@item:inlistbox <model name> (<size on disk>), the model is already downloaded",
                     "%1 (%2, downloaded)",
                     info.name,
                     modelSize(info.sizeMib));
    }
    return i18nc("@item:inlistbox <model name> (<size on disk>)", "%1 (%2)", info.name, modelSize(info.sizeMib));
}

[[nodiscard]] QString modelToolTip(const WhisperSpeechToTextModelsJob::ModelInfo &info)
{
    QString toolTip = info.multilingual ? i18nc("@info:tooltip", "Transcribes every language whisper knows.")
                                        : i18nc("@info:tooltip", "Transcribes english only, but about twice as fast.");
    toolTip += u'\n';
    toolTip += i18nc("@info:tooltip", "Takes %1 on disk, downloaded the first time it is used.", modelSize(info.sizeMib));
    if (info.isDefault) {
        toolTip += u'\n';
        toolTip += i18nc("@info:tooltip", "Used when no model was chosen.");
    }
    return toolTip;
}
}

WhisperSpeechToTextModelComboBox::WhisperSpeechToTextModelComboBox(QWidget *parent)
    : QComboBox(parent)
{
    connect(this, &QComboBox::currentIndexChanged, this, &WhisperSpeechToTextModelComboBox::slotCurrentIndexChanged);
}

WhisperSpeechToTextModelComboBox::~WhisperSpeechToTextModelComboBox() = default;

void WhisperSpeechToTextModelComboBox::fill()
{
    auto job = new WhisperSpeechToTextModelsJob(this);
    connect(job, &WhisperSpeechToTextModelsJob::modelsLoaded, this, [this](const WhisperSpeechToTextModelsJob::ModelInfos &models) {
        setModels(models);
        Q_EMIT modelsLoaded();
    });
    connect(job, &WhisperSpeechToTextModelsJob::modelsFailed, this, &WhisperSpeechToTextModelComboBox::modelsFailed);
    job->start();
    // Two answers rather than one: the table comes back right away, while what is
    // on disk costs the start of huggingface_hub. The list must not wait for it.
    refreshCachedModels();
}

void WhisperSpeechToTextModelComboBox::refreshCachedModels()
{
    auto job = new WhisperSpeechToTextCachedModelsJob(this);
    connect(job, &WhisperSpeechToTextCachedModelsJob::cachedModelsLoaded, this, [this](const QStringList &models) {
        setCachedModels(models);
        Q_EMIT cachedModelsLoaded();
    });
    // Nothing is marked when it could not be asked: the models are all offered,
    // and the one which is picked is downloaded when it is used.
    job->start();
}

void WhisperSpeechToTextModelComboBox::setCachedModels(const QStringList &identifiers)
{
    mCachedModels = identifiers;
    mCachedModelsKnown = true;
    updateItems();
}

bool WhisperSpeechToTextModelComboBox::cachedModelsKnown() const
{
    return mCachedModelsKnown;
}

QStringList WhisperSpeechToTextModelComboBox::cachedModels() const
{
    return mCachedModels;
}

bool WhisperSpeechToTextModelComboBox::isModelDownloaded(const QString &identifier) const
{
    return mCachedModels.contains(identifier);
}

void WhisperSpeechToTextModelComboBox::updateItems()
{
    // Only the texts change: the items stay where they are, so the selection and
    // what it means to the caller are untouched.
    for (int i = 0, total = count(); i < total && i < mModels.count(); ++i) {
        setItemText(i, modelLabel(mModels.at(i), isModelDownloaded(mModels.at(i).identifier)));
    }
}

void WhisperSpeechToTextModelComboBox::setModels(const WhisperSpeechToTextModelsJob::ModelInfos &models)
{
    // Filling is not the user choosing a model: no signal for the items which
    // are only passed through on the way to the selected one.
    mFilling = true;
    clear();
    mModels = models;
    mDefaultModel = WhisperSpeechToTextModelsJob::defaultModel(models);
    for (const WhisperSpeechToTextModelsJob::ModelInfo &info : models) {
        addItem(modelLabel(info, isModelDownloaded(info.identifier)), info.identifier);
        setItemData(count() - 1, modelToolTip(info), Qt::ToolTipRole);
    }
    // What was asked for before the models were there is what is selected now,
    // and landing on it is still the filling, not the user choosing a model: a
    // dialog must not believe that it has something to save.
    setCurrentModel(mPendingModel);
    mFilling = false;
}

QString WhisperSpeechToTextModelComboBox::currentModel() const
{
    return currentData().toString();
}

void WhisperSpeechToTextModelComboBox::setCurrentModel(const QString &identifier)
{
    mPendingModel = identifier;
    if (count() == 0) {
        // The listing has not answered yet: setModels() applies it.
        return;
    }
    int index = findData(identifier);
    if (index == -1) {
        // Nothing chosen, or a model the script does not offer anymore.
        index = findData(mDefaultModel);
    }
    setCurrentIndex(qMax(0, index));
}

void WhisperSpeechToTextModelComboBox::slotCurrentIndexChanged()
{
    if (!mFilling) {
        Q_EMIT currentModelChanged(currentModel());
    }
}

#include "moc_whisperspeechtotextmodelcombobox.cpp"
