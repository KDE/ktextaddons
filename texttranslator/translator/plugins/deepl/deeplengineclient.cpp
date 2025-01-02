/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "deeplengineclient.h"
#include "deeplengineconfiguredialog.h"
#include "deeplengineplugin.h"
#include "deeplengineutil.h"
#include "deepltranslator_debug.h"
#include "translator/misc/translatorutil.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QPointer>
#include <qt6keychain/keychain.h>

DeeplEngineClient::DeeplEngineClient(QObject *parent)
    : TextTranslator::TranslatorEngineClient{parent}
{
}

DeeplEngineClient::~DeeplEngineClient() = default;

QString DeeplEngineClient::name() const
{
    return QStringLiteral("deepl");
}

QString DeeplEngineClient::translatedName() const
{
    return i18n("DeepL");
}

TextTranslator::TranslatorEnginePlugin *DeeplEngineClient::createTranslator()
{
    auto enginePlugin = new DeeplEnginePlugin();
    connect(this, &DeeplEngineClient::configureChanged, enginePlugin, &DeeplEnginePlugin::slotConfigureChanged);
    return enginePlugin;
}

QMap<TextTranslator::TranslatorUtil::Language, QString> DeeplEngineClient::supportedFromLanguages()
{
    if (mFromLanguages.isEmpty()) {
        mFromLanguages = fillLanguages();
    }
    return mFromLanguages;
}

QMap<TextTranslator::TranslatorUtil::Language, QString> DeeplEngineClient::supportedToLanguages()
{
    return supportedFromLanguages();
}

bool DeeplEngineClient::isSupported(TextTranslator::TranslatorUtil::Language lang) const
{
    switch (lang) {
    case TextTranslator::TranslatorUtil::automatic:
    case TextTranslator::TranslatorUtil::bg:
    case TextTranslator::TranslatorUtil::cs:
    case TextTranslator::TranslatorUtil::da:
    case TextTranslator::TranslatorUtil::de:
    case TextTranslator::TranslatorUtil::en:
    case TextTranslator::TranslatorUtil::el:
    case TextTranslator::TranslatorUtil::es:
    case TextTranslator::TranslatorUtil::et:
    case TextTranslator::TranslatorUtil::fi:
    case TextTranslator::TranslatorUtil::fr:
    case TextTranslator::TranslatorUtil::hu:
    case TextTranslator::TranslatorUtil::id:
    case TextTranslator::TranslatorUtil::it:
    case TextTranslator::TranslatorUtil::ja:
    case TextTranslator::TranslatorUtil::lt:
    case TextTranslator::TranslatorUtil::lv:
    case TextTranslator::TranslatorUtil::nl:
    case TextTranslator::TranslatorUtil::pl:
    case TextTranslator::TranslatorUtil::pt:
    case TextTranslator::TranslatorUtil::ro:
    case TextTranslator::TranslatorUtil::ru:
    case TextTranslator::TranslatorUtil::sk:
    case TextTranslator::TranslatorUtil::sl:
    case TextTranslator::TranslatorUtil::sv:
    case TextTranslator::TranslatorUtil::tr:
    case TextTranslator::TranslatorUtil::uk:
    case TextTranslator::TranslatorUtil::zh:
        return true;
    default:
        break;
    }
    return false;
}

bool DeeplEngineClient::hasConfigurationDialog() const
{
    return true;
}

bool DeeplEngineClient::showConfigureDialog(QWidget *parentWidget)
{
    bool settingsChanged = false;
    QPointer<DeeplEngineConfigureDialog> dlg = new DeeplEngineConfigureDialog(parentWidget);
    KConfigGroup myGroup(KSharedConfig::openConfig(), DeeplEngineUtil::groupName());
    dlg->setUseFreeLicenceKey(myGroup.readEntry(DeeplEngineUtil::freeLicenseKey(), false));

    auto readJob = new QKeychain::ReadPasswordJob(DeeplEngineUtil::translatorGroupName(), this);
    connect(readJob, &QKeychain::Job::finished, this, [dlg](QKeychain::Job *baseJob) {
        auto job = qobject_cast<QKeychain::ReadPasswordJob *>(baseJob);
        Q_ASSERT(job);
        if (job->error()) {
            qCWarning(TRANSLATOR_DEEPL_LOG) << "We have an error during reading password " << job->errorString();
        } else {
            dlg->setApiKey(job->textData());
        }
    });
    readJob->setKey(DeeplEngineUtil::apiGroupName());
    readJob->start();
    if (dlg->exec()) {
        myGroup.writeEntry(DeeplEngineUtil::freeLicenseKey(), dlg->useFreeLicenceKey());
        myGroup.sync();

        auto writeJob = new QKeychain::WritePasswordJob(DeeplEngineUtil::translatorGroupName(), this);
        connect(writeJob, &QKeychain::Job::finished, this, &DeeplEngineClient::slotPasswordWritten);
        writeJob->setKey(DeeplEngineUtil::apiGroupName());
        writeJob->setTextData(dlg->apiKey());
        writeJob->start();
        Q_EMIT configureChanged();
        settingsChanged = true;
    }
    delete dlg;
    return settingsChanged;
}

TextTranslator::TranslatorEngineClient::EngineType DeeplEngineClient::engineType() const
{
    return TextTranslator::TranslatorEngineClient::Network;
}

void DeeplEngineClient::slotPasswordWritten(QKeychain::Job *baseJob)
{
    if (baseJob->error()) {
        qCWarning(TRANSLATOR_DEEPL_LOG) << "Error writing password using QKeychain:" << baseJob->errorString();
    }
}

#include "moc_deeplengineclient.cpp"
