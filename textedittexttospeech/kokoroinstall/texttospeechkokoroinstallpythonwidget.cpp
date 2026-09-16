/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "texttospeechkokoroinstallpythonwidget.h"
#include "texttospeechkokorodownloadvoicejob.h"
#include "texttospeechkokoroinstalljob.h"
#include "texttospeechkokoroinstallpythonevenvjob.h"
#include "texttospeechkokoroutils.h"
#include "texttospeechkokorovoicecombobox.h"
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
using namespace TextEditTextToSpeech;
using namespace Qt::Literals::StringLiterals;

namespace
{
// What the check reported, without espeak-ng: it is a system package, pip knows
// nothing under that name.
[[nodiscard]] QStringList pipModules(const QStringList &modules)
{
    QStringList result = modules;
    result.removeAll("espeak-ng"_L1);
    return result;
}
}
TextToSpeechKokoroInstallPythonWidget::TextToSpeechKokoroInstallPythonWidget(QWidget *parent)
    : QWidget{parent}
    , mPlainTextEdit(new QPlainTextEdit(this))
    , mKokoroVoiceComboBox(new TextToSpeechKokoroVoiceComboBox(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mPlainTextEdit->setObjectName(u"mPlainTextEdit"_s);
    mPlainTextEdit->setReadOnly(true);
    mKokoroVoiceComboBox->setObjectName(u"mKokoroVoiceComboBox"_s);
    mainLayout->addWidget(mPlainTextEdit);
    auto hboxLayout = new QHBoxLayout;
    hboxLayout->setContentsMargins({});
    mainLayout->addLayout(hboxLayout);
    hboxLayout->addWidget(new QLabel(i18n("Select Voice(s):"), this));
    hboxLayout->addWidget(mKokoroVoiceComboBox, 1);
    auto pushButton = new QPushButton(i18n("Download Voice(s)"), this);
    hboxLayout->addWidget(pushButton);
    connect(pushButton, &QPushButton::clicked, this, [this]() {
        auto job = new TextToSpeechKokoroDownloadVoiceJob(this);
        job->setVoices(mKokoroVoiceComboBox->selectedVoices());
        Q_EMIT installInProgress(true);
        connect(job, &TextToSpeechKokoroDownloadVoiceJob::downloadVoicesDone, this, [this]() {
            appendMessage(i18n("Download Voices done."));
            Q_EMIT installInProgress(false);
        });
        connect(job, &TextToSpeechKokoroDownloadVoiceJob::downloadVoicesFailed, this, [this]() {
            appendMessage(i18n("Unable to download voice."));
            Q_EMIT installInProgress(false);
        });
        connect(job, &TextToSpeechKokoroDownloadVoiceJob::downloadMessage, this, [this](const QString &msg) {
            appendMessage(msg);
        });
        job->start();
    });
    mKokoroVoiceComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

TextToSpeechKokoroInstallPythonWidget::~TextToSpeechKokoroInstallPythonWidget() = default;

QStringList TextToSpeechKokoroInstallPythonWidget::modules() const
{
    return mModules;
}

void TextToSpeechKokoroInstallPythonWidget::setModules(const QStringList &newModules)
{
    mModules = newModules;
}

void TextToSpeechKokoroInstallPythonWidget::startInstall()
{
    // espeak-ng is a system package, only the distribution can install it.
    if (mModules.contains("espeak-ng"_L1)) {
        appendMessage(i18n("espeak-ng is missing. Please install it with your package manager."));
    }
    // Recreating the virtualenv for nothing would throw away a working one.
    if (pipModules(mModules).isEmpty()) {
        appendMessage(i18n("Nothing to install."));
        // The caller disabled what it had to before calling us, it has to be told that it is over.
        Q_EMIT installInProgress(false);
        Q_EMIT installDone();
        return;
    }
    appendMessage(i18n("Creating the python virtual environment…"));
    auto job = new TextToSpeechKokoroInstallPythonEvenvJob(this);
    connect(job, &TextToSpeechKokoroInstallPythonEvenvJob::installDone, this, [this]() {
        appendMessage(i18n("Python virtual environment created."));
        installModules();
    });
    connect(job, &TextToSpeechKokoroInstallPythonEvenvJob::installFailed, this, [this]() {
        appendMessage(i18n("Unable to create the python virtual environment."));
        Q_EMIT installFailed();
    });
    job->start();
}

void TextToSpeechKokoroInstallPythonWidget::installModules()
{
    // The virtualenv was just recreated from scratch: installing only the modules
    // the check reported as missing would leave out the ones it had found in the
    // previous one, and kokoro would still not be usable.
    QStringList modules = TextToSpeechKokoroUtils::requiredModules();
    for (const QString &module : pipModules(mModules)) {
        if (!modules.contains(module)) {
            modules.append(module);
        }
    }
    appendMessage(i18n("Installing modules: %1", modules.join(", "_L1)));
    auto job = new TextToSpeechKokoroInstallJob(this);
    job->setModules(modules);
    connect(job, &TextToSpeechKokoroInstallJob::installMessage, this, &TextToSpeechKokoroInstallPythonWidget::appendMessage);
    connect(job, &TextToSpeechKokoroInstallJob::installDone, this, [this]() {
        appendMessage(i18n("Installation done."));
        Q_EMIT installDone();
    });
    connect(job, &TextToSpeechKokoroInstallJob::installFailed, this, [this]() {
        appendMessage(i18n("Installation failed."));
        Q_EMIT installFailed();
    });
    job->start();
}

void TextToSpeechKokoroInstallPythonWidget::appendMessage(const QString &message)
{
    // pip output already ends with a newline, appendPlainText would add an empty line.
    const QString text = message.trimmed();
    if (!text.isEmpty()) {
        mPlainTextEdit->appendPlainText(text);
    }
}

#include "moc_texttospeechkokoroinstallpythonwidget.cpp"
