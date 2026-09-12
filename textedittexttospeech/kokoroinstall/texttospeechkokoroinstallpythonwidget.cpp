/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "texttospeechkokoroinstallpythonwidget.h"
#include "texttospeechkokoroinstalljob.h"
#include "texttospeechkokoroinstallpythonevenvjob.h"
#include "texttospeechkokorovoicecombobox.h"
#include <KLocalizedString>
#include <QPlainTextEdit>
#include <QVBoxLayout>

using namespace TextEditTextToSpeech;
using namespace Qt::Literals::StringLiterals;
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
    mainLayout->addWidget(mKokoroVoiceComboBox);
    mainLayout->addWidget(mPlainTextEdit);
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
    appendMessage(i18n("Installing modules: %1", mModules.join(", "_L1)));
    auto job = new TextToSpeechKokoroInstallJob(this);
    job->setModules(mModules);
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
