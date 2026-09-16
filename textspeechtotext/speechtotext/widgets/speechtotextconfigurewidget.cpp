/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotextconfigurewidget.h"

#include "speechtotext/speechtotextmanager.h"
#include "speechtotext/widgets/speechtotextlanguagecomboboxwidget.h"
#include "speechtotextenginecomboboxwidget.h"
#include "speechtotextselectdevicewidget.h"
#include "whisperspeechtotextcheckjob.h"
#include "whisperspeechtotextinstallmessagewidget.h"
#include "whisperspeechtotextinstallpythondialog.h"
#include <KLocalizedString>
#include <QPointer>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
using namespace TextSpeechToText;

SpeechToTextConfigureWidget::SpeechToTextConfigureWidget(QWidget *parent)
    : QWidget{parent}
    , mSpeechToTextComboBox(new SpeechToTextEngineComboBoxWidget(this))
    , mSpeechToTextDevice(new SpeechToTextSelectDeviceWidget(this))
    , mSpeechToTextLanguage(new SpeechToTextLanguageComboBoxWidget(this))
    , mWhisperInstallMessageWidget(new WhisperSpeechToTextInstallMessageWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mWhisperInstallMessageWidget->setObjectName(u"mWhisperInstallMessageWidget"_s);
    mWhisperInstallMessageWidget->hide();
    mainLayout->addWidget(mWhisperInstallMessageWidget);

    mSpeechToTextDevice->setObjectName(u"mSpeechToTextDevice"_s);
    mainLayout->addWidget(mSpeechToTextDevice);

    mSpeechToTextComboBox->setObjectName(u"mSpeechToTextComboBox"_s);
    mainLayout->addWidget(mSpeechToTextComboBox);

    mSpeechToTextLanguage->setObjectName(u"mSpeechToTextLanguage"_s);
    mainLayout->addWidget(mSpeechToTextLanguage);

    mSpeechToTextComboBox->fillEngine();

    // Connected after fillEngine(): filling the combobox is not the user selecting an engine.
    connect(mSpeechToTextComboBox, &SpeechToTextEngineComboBoxWidget::engineChanged, this, &SpeechToTextConfigureWidget::slotEngineChanged);
    connect(mWhisperInstallMessageWidget, &WhisperSpeechToTextInstallMessageWidget::installPackages, this, &SpeechToTextConfigureWidget::slotInstallWhisper);
}

SpeechToTextConfigureWidget::~SpeechToTextConfigureWidget() = default;

void SpeechToTextConfigureWidget::loadSettings()
{
    mSpeechToTextComboBox->load();
    mSpeechToTextDevice->loadSettings();
    // load() does not necessarily change the current index, so the check is asked for explicitly.
    slotEngineChanged(mSpeechToTextComboBox->engineName());
}

void SpeechToTextConfigureWidget::saveSettings()
{
    mSpeechToTextComboBox->save();
    mSpeechToTextDevice->saveSettings();
    // Apply right away: the user just selected the engine, they shouldn't have to restart.
    SpeechToTextManager::self()->loadEngine();
}

void SpeechToTextConfigureWidget::slotEngineChanged(const QString &engineName)
{
    if (engineName == "whisper"_L1) {
        checkWhisperEngine();
    } else {
        mWhisperInstallMessageWidget->animatedHide();
    }
}

void SpeechToTextConfigureWidget::checkWhisperEngine()
{
    auto job = new WhisperSpeechToTextCheckJob(this);
    connect(job, &WhisperSpeechToTextCheckJob::packagesInstalled, this, [this]() {
        mWhisperInstallMessageWidget->animatedHide();
    });
    connect(job, &WhisperSpeechToTextCheckJob::needToInstallPackages, this, [this](const QStringList &missing) {
        mWhisperInstallMessageWidget->setText(i18n("Whisper is not installed. Missing: %1", missing.join(", "_L1)));
        mWhisperInstallMessageWidget->setMissingPackages(missing);
        mWhisperInstallMessageWidget->animatedShow();
    });
    connect(job, &WhisperSpeechToTextCheckJob::needToReinstall, this, [this]() {
        mWhisperInstallMessageWidget->setText(i18n("Whisper installation is broken. Please reinstall it."));
        mWhisperInstallMessageWidget->setMissingPackages({});
        mWhisperInstallMessageWidget->animatedShow();
    });
    job->start();
}

void SpeechToTextConfigureWidget::slotInstallWhisper(const QStringList &modules)
{
    QPointer<WhisperSpeechToTextInstallPythonDialog> dlg = new WhisperSpeechToTextInstallPythonDialog(this);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->setModules(modules);
    dlg->show();
    dlg->startInstall();
}

#include "moc_speechtotextconfigurewidget.cpp"
