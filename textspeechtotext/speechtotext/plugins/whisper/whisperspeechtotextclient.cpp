/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "whisperspeechtotextclient.h"

#include "whisperspeechtotextcheckjob.h"
#include "whisperspeechtotextinstallpythondialog.h"
#include "whisperspeechtotextplugin.h"
#include "whisperspeechtotextutils.h"
#include <KLocalizedString>
#include <QPointer>

using namespace Qt::Literals::StringLiterals;
WhisperSpeechToTextClient::WhisperSpeechToTextClient(QObject *parent)
    : TextSpeechToText::SpeechToTextClient{parent}
{
}

WhisperSpeechToTextClient::~WhisperSpeechToTextClient() = default;

QString WhisperSpeechToTextClient::name() const
{
    return u"whisper"_s;
}

QString WhisperSpeechToTextClient::translatedName() const
{
    return i18n("Whisper");
}

TextSpeechToText::SpeechToTextClient::EngineType WhisperSpeechToTextClient::engineType() const
{
    return TextSpeechToText::SpeechToTextClient::Locale;
}

TextSpeechToText::SpeechToTextPlugin *WhisperSpeechToTextClient::createTextToSpeech()
{
    return new WhisperSpeechToTextPlugin;
}

bool WhisperSpeechToTextClient::hasConfigurationDialog() const
{
    return true;
}

bool WhisperSpeechToTextClient::showConfigureDialog(QWidget *parentWidget)
{
    // The dialog installs what the check reported as missing: without asking for it
    // first, it would have nothing to install.
    const QString previousModel = WhisperSpeechToTextUtils::loadModel();
    const WhisperSpeechToTextCheckJob::CheckResult result = WhisperSpeechToTextCheckJob::checkSynchronously();
    // A broken installation names nothing: everything whisper needs is reinstalled.
    const QStringList modules = result.needToReinstall ? WhisperSpeechToTextUtils::requiredModules() : result.missing;

    bool installSucceeded = false;
    QPointer<WhisperSpeechToTextInstallPythonDialog> dlg = new WhisperSpeechToTextInstallPythonDialog(parentWidget);
    dlg->setModules(modules);
    connect(dlg, &WhisperSpeechToTextInstallPythonDialog::installDone, this, [&installSucceeded]() {
        installSucceeded = true;
    });
    // exec() is what runs the event loop the jobs need, so the install is started before it.
    dlg->startInstall();
    dlg->exec();
    delete dlg;

    // Nothing was installed when there was nothing missing, but the dialog is also
    // where the model is chosen, and the engine has to be rebuilt to use it.
    const bool settingsChanged = (!modules.isEmpty() && installSucceeded) || previousModel != WhisperSpeechToTextUtils::loadModel();
    if (settingsChanged) {
        Q_EMIT configureChanged();
    }
    return settingsChanged;
}

#include "moc_whisperspeechtotextclient.cpp"
