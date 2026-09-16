/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextinstallpythonwidget.h"
#include "whisperspeechtotextdownloadmodeljob.h"
#include "whisperspeechtotextinstalljob.h"
#include "whisperspeechtotextinstallpythonevenvjob.h"
#include "whisperspeechtotextmodelcombobox.h"
#include "whisperspeechtotextutils.h"
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QLabel>
#include <QLocale>
#include <QPlainTextEdit>
#include <QProgressBar>
#include <QPushButton>
#include <QVBoxLayout>
#include <utility>

using namespace Qt::Literals::StringLiterals;

WhisperSpeechToTextInstallPythonWidget::WhisperSpeechToTextInstallPythonWidget(QWidget *parent)
    : QWidget{parent}
    , mPlainTextEdit(new QPlainTextEdit(this))
    , mModelComboBox(new WhisperSpeechToTextModelComboBox(this))
    , mDownloadModelButton(new QPushButton(i18nc("@action:button", "Download Model"), this))
    , mDownloadProgressBar(new QProgressBar(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mPlainTextEdit->setObjectName(u"mPlainTextEdit"_s);
    mPlainTextEdit->setReadOnly(true);
    mainLayout->addWidget(mPlainTextEdit);

    mDownloadProgressBar->setObjectName(u"mDownloadProgressBar"_s);
    mDownloadProgressBar->setRange(0, 100);
    // Nothing is being downloaded yet: an empty bar would only be in the way.
    mDownloadProgressBar->hide();
    mainLayout->addWidget(mDownloadProgressBar);

    auto modelLayout = new QHBoxLayout;
    modelLayout->setObjectName(u"modelLayout"_s);
    modelLayout->setContentsMargins({});
    mainLayout->addLayout(modelLayout);

    // "Model:" alone, next to a download button, reads as the model to download.
    auto modelLabel = new QLabel(i18nc("@label:listbox", "Model used for dictation:"), this);
    modelLabel->setObjectName(u"modelLabel"_s);
    modelLayout->addWidget(modelLabel);

    mModelComboBox->setObjectName(u"mModelComboBox"_s);
    modelLayout->addWidget(mModelComboBox, 1);

    mDownloadModelButton->setObjectName(u"mDownloadModelButton"_s);
    // There is nothing to download as long as the models are not listed.
    mDownloadModelButton->setEnabled(false);
    modelLayout->addWidget(mDownloadModelButton);

    connect(mDownloadModelButton, &QPushButton::clicked, this, &WhisperSpeechToTextInstallPythonWidget::downloadModel);
    connect(mModelComboBox, &WhisperSpeechToTextModelComboBox::modelsLoaded, this, [this]() {
        mDownloadModelButton->setEnabled(true);
    });
    // A listing which failed leaves an empty box and a disabled button, which is
    // what there is to say: the job is the one which logs why.
    // The dialog has no button to apply anything: the model is stored as it is
    // chosen, and the engine is told about it by WhisperSpeechToTextClient.
    connect(mModelComboBox, &WhisperSpeechToTextModelComboBox::currentModelChanged, this, [this](const QString &model) {
        WhisperSpeechToTextUtils::saveModel(model);
        warnWhenModelIsNotDownloaded();
    });
    // What is on disk is known after the list is shown: the model which was
    // already chosen is only known to be missing then.
    connect(mModelComboBox, &WhisperSpeechToTextModelComboBox::cachedModelsLoaded, this, &WhisperSpeechToTextInstallPythonWidget::warnWhenModelIsNotDownloaded);
    mModelComboBox->setCurrentModel(WhisperSpeechToTextUtils::loadModel());
    mModelComboBox->fill();
}

WhisperSpeechToTextInstallPythonWidget::~WhisperSpeechToTextInstallPythonWidget() = default;

QStringList WhisperSpeechToTextInstallPythonWidget::modules() const
{
    return mModules;
}

void WhisperSpeechToTextInstallPythonWidget::setModules(const QStringList &newModules)
{
    mModules = newModules;
}

void WhisperSpeechToTextInstallPythonWidget::startInstall()
{
    if (mModules.isEmpty()) {
        appendMessage(i18n("Nothing to install."));
        // The caller disabled what it had to before calling us, it has to be told that it is over.
        Q_EMIT installInProgress(false);
        Q_EMIT installDone();
        return;
    }
    Q_EMIT installInProgress(true);
    appendMessage(i18n("Creating the python virtual environment…"));
    auto evenvJob = new WhisperSpeechToTextInstallPythonEvenvJob(this);
    connect(evenvJob, &WhisperSpeechToTextInstallPythonEvenvJob::installDone, this, [this]() {
        appendMessage(i18n("Python virtual environment created."));
        installModules();
    });
    connect(evenvJob, &WhisperSpeechToTextInstallPythonEvenvJob::installFailed, this, [this]() {
        appendMessage(i18n("Unable to create the python virtual environment."));
        Q_EMIT installInProgress(false);
        Q_EMIT installFailed();
    });
    evenvJob->start();
}

void WhisperSpeechToTextInstallPythonWidget::installModules()
{
    // The virtualenv was just recreated from scratch: installing only the modules
    // the check reported as missing would leave out the ones it had found in the
    // previous one, and whisper would still not be usable.
    QStringList modules = WhisperSpeechToTextUtils::requiredModules();
    for (const QString &module : std::as_const(mModules)) {
        if (!modules.contains(module)) {
            modules.append(module);
        }
    }
    appendMessage(i18n("Installing modules in %1: %2", WhisperSpeechToTextUtils::defaultVenvPath(), modules.join(", "_L1)));
    auto job = new WhisperSpeechToTextInstallJob(this);
    job->setModules(modules);
    connect(job, &WhisperSpeechToTextInstallJob::installMessage, this, &WhisperSpeechToTextInstallPythonWidget::appendMessage);
    connect(job, &WhisperSpeechToTextInstallJob::installDone, this, [this]() {
        appendMessage(i18n("Installation done."));
        Q_EMIT installInProgress(false);
        Q_EMIT installDone();
    });
    connect(job, &WhisperSpeechToTextInstallJob::installFailed, this, [this]() {
        appendMessage(i18n("Installation failed."));
        Q_EMIT installInProgress(false);
        Q_EMIT installFailed();
    });
    job->start();
}

void WhisperSpeechToTextInstallPythonWidget::downloadModel()
{
    const QString model = mModelComboBox->currentModel();
    if (model.isEmpty()) {
        return;
    }
    auto job = new WhisperSpeechToTextDownloadModelJob(this);
    job->setModel(model);
    connect(job, &WhisperSpeechToTextDownloadModelJob::downloadMessage, this, &WhisperSpeechToTextInstallPythonWidget::appendMessage);
    connect(job, &WhisperSpeechToTextDownloadModelJob::downloadProgress, this, [this](int percent, qint64 received, qint64 total) {
        mDownloadProgressBar->setValue(percent);
        // The percentage is what the bar shows by itself: the sizes are what
        // tells the user whether the wait is a minute or an hour.
        mDownloadProgressBar->setFormat(i18nc("@info:progress <downloaded> of <size of the model>",
                                              "%1 of %2",
                                              QLocale().formattedDataSize(received, 1),
                                              QLocale().formattedDataSize(total, 1)));
    });
    connect(job, &WhisperSpeechToTextDownloadModelJob::downloadModelDone, this, [this]() {
        setDownloadInProgress(false);
        // The model is on disk now, and the list says so.
        mModelComboBox->refreshCachedModels();
    });
    connect(job, &WhisperSpeechToTextDownloadModelJob::downloadModelFailed, this, [this, model]() {
        appendMessage(i18n("Unable to download the %1 model.", model));
        setDownloadInProgress(false);
    });
    setDownloadInProgress(true);
    job->start();
}

void WhisperSpeechToTextInstallPythonWidget::warnWhenModelIsNotDownloaded()
{
    const QString model = mModelComboBox->currentModel();
    // Nothing to say as long as the cache was not looked at: not knowing is not
    // the same as knowing that the model is missing.
    if (model.isEmpty() || !mModelComboBox->cachedModelsKnown() || mModelComboBox->isModelDownloaded(model)) {
        return;
    }
    appendMessage(
        i18n("The %1 model is not on disk: it is downloaded the first time it is used, which makes that dictation a long one. "
             "The Download Model button does it now.",
             model));
}

void WhisperSpeechToTextInstallPythonWidget::setDownloadInProgress(bool inProgress)
{
    // Changing the model or closing the dialog in the middle would kill the download.
    mDownloadModelButton->setEnabled(!inProgress);
    mModelComboBox->setEnabled(!inProgress);
    mDownloadProgressBar->setVisible(inProgress);
    if (inProgress) {
        mDownloadProgressBar->setValue(0);
        // Until the first bytes arrive, the size of what is coming is unknown.
        mDownloadProgressBar->setFormat(u"%p%"_s);
    }
    Q_EMIT installInProgress(inProgress);
}

void WhisperSpeechToTextInstallPythonWidget::appendMessage(const QString &message)
{
    // pip output already ends with a newline, appendPlainText would add an empty line.
    const QString text = message.trimmed();
    if (!text.isEmpty()) {
        mPlainTextEdit->appendPlainText(text);
    }
}

#include "moc_whisperspeechtotextinstallpythonwidget.cpp"
