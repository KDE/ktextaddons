/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextinstallpythonwidget.h"
#include "whisperspeechtotextinstalljob.h"
#include "whisperspeechtotextinstallpythonevenvjob.h"
#include "whisperspeechtotextutils.h"
#include <KLocalizedString>
#include <QPlainTextEdit>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;

WhisperSpeechToTextInstallPythonWidget::WhisperSpeechToTextInstallPythonWidget(QWidget *parent)
    : QWidget{parent}
    , mPlainTextEdit(new QPlainTextEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mPlainTextEdit->setObjectName(u"mPlainTextEdit"_s);
    mPlainTextEdit->setReadOnly(true);
    mainLayout->addWidget(mPlainTextEdit);
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
    appendMessage(i18n("Installing modules in %1: %2", WhisperSpeechToTextUtils::defaultVenvPath(), mModules.join(", "_L1)));
    auto job = new WhisperSpeechToTextInstallJob(this);
    job->setModules(mModules);
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

void WhisperSpeechToTextInstallPythonWidget::appendMessage(const QString &message)
{
    // pip output already ends with a newline, appendPlainText would add an empty line.
    const QString text = message.trimmed();
    if (!text.isEmpty()) {
        mPlainTextEdit->appendPlainText(text);
    }
}

#include "moc_whisperspeechtotextinstallpythonwidget.cpp"
