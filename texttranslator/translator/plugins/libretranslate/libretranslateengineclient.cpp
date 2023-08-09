/*
  SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "libretranslateengineclient.h"
#include "libretranslateengineconfiguredialog.h"
#include "libretranslateengineplugin.h"
#include "libretranslateengineutil.h"
#include "libretranslatetranslator_debug.h"
#include "translator/misc/translatorutil.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QPointer>
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#include <qt5keychain/keychain.h>
#else
#include <qt6keychain/keychain.h>
#endif

LibreTranslateEngineClient::LibreTranslateEngineClient(QObject *parent)
    : TextTranslator::TranslatorEngineClient{parent}
{
}

LibreTranslateEngineClient::~LibreTranslateEngineClient() = default;

QString LibreTranslateEngineClient::name() const
{
    return QStringLiteral("libretranslate");
}

QString LibreTranslateEngineClient::translatedName() const
{
    return i18n("Libre Translate");
}

TextTranslator::TranslatorEnginePlugin *LibreTranslateEngineClient::createTranslator()
{
    auto enginePlugin = new LibreTranslateEnginePlugin();
    connect(this, &LibreTranslateEngineClient::configureChanged, enginePlugin, &LibreTranslateEnginePlugin::slotConfigureChanged);
    return enginePlugin;
}

QMap<TextTranslator::TranslatorUtil::Language, QString> LibreTranslateEngineClient::supportedFromLanguages()
{
    if (mFromLanguages.isEmpty()) {
        mFromLanguages = fillLanguages();
    }
    return mFromLanguages;
}

QMap<TextTranslator::TranslatorUtil::Language, QString> LibreTranslateEngineClient::supportedToLanguages()
{
    return supportedFromLanguages();
}

bool LibreTranslateEngineClient::hasConfigurationDialog() const
{
    return true;
}

bool LibreTranslateEngineClient::showConfigureDialog(QWidget *parentWidget)
{
    bool settingsChanged = false;
    QPointer<LibreTranslateEngineConfigureDialog> dlg = new LibreTranslateEngineConfigureDialog(parentWidget);
    KConfigGroup myGroup(KSharedConfig::openConfig(), LibreTranslateEngineUtil::groupName());
    QString serverUrlFromConfig = myGroup.readEntry(LibreTranslateEngineUtil::serverUrlKey(), LibreTranslateEngineUtil::defaultServerUrl());
    if (serverUrlFromConfig.isEmpty()) {
        serverUrlFromConfig = LibreTranslateEngineUtil::defaultServerUrl();
    }
    serverUrlFromConfig = LibreTranslateEngineUtil::adaptUrl(serverUrlFromConfig);
    dlg->setServerUrl(serverUrlFromConfig);
    dlg->setServerRequiredApiKey(myGroup.readEntry(LibreTranslateEngineUtil::serverRequiredApiKey(), false));
    auto readJob = new QKeychain::ReadPasswordJob(LibreTranslateEngineUtil::translatorGroupName(), this);
    connect(readJob, &QKeychain::Job::finished, this, [dlg](QKeychain::Job *baseJob) {
        auto job = qobject_cast<QKeychain::ReadPasswordJob *>(baseJob);
        Q_ASSERT(job);
        if (job->error()) {
            qCWarning(TRANSLATOR_LIBRETRANSLATE_LOG) << "We have an error during reading password " << job->errorString();
        } else {
            dlg->setApiKey(job->textData());
        }
    });
    if (dlg->exec()) {
        const QString serverUrl = dlg->serverUrl();
        const bool requiredApiKey = dlg->serverRequiredApiKey();
        myGroup.writeEntry(LibreTranslateEngineUtil::serverUrlKey(), serverUrl);
        myGroup.writeEntry(LibreTranslateEngineUtil::serverRequiredApiKey(), requiredApiKey);
        auto writeJob = new QKeychain::WritePasswordJob(LibreTranslateEngineUtil::translatorGroupName(), this);
        connect(writeJob, &QKeychain::Job::finished, this, &LibreTranslateEngineClient::slotPasswordWritten);
        writeJob->setKey(LibreTranslateEngineUtil::apiGroupName());
        writeJob->setTextData(dlg->apiKey());
        writeJob->start();
        myGroup.sync();
        Q_EMIT configureChanged();
        settingsChanged = true;
    }
    delete dlg;
    return settingsChanged;
}

TextTranslator::TranslatorEngineClient::EngineType LibreTranslateEngineClient::engineType() const
{
    return TextTranslator::TranslatorEngineClient::Network;
}

void LibreTranslateEngineClient::slotPasswordWritten(QKeychain::Job *baseJob)
{
    if (baseJob->error()) {
        qCWarning(TRANSLATOR_LIBRETRANSLATE_LOG) << "Error writing password using QKeychain:" << baseJob->errorString();
    }
}

bool LibreTranslateEngineClient::isSupported(TextTranslator::TranslatorUtil::Language lang) const
{
    switch (lang) {
    case TextTranslator::TranslatorUtil::sq:
    case TextTranslator::TranslatorUtil::af:
    case TextTranslator::TranslatorUtil::hy:
    case TextTranslator::TranslatorUtil::az:
    case TextTranslator::TranslatorUtil::eu:
    case TextTranslator::TranslatorUtil::be:
    case TextTranslator::TranslatorUtil::bs:
    case TextTranslator::TranslatorUtil::bg:
    case TextTranslator::TranslatorUtil::ca:
    case TextTranslator::TranslatorUtil::hr:
    case TextTranslator::TranslatorUtil::cs:
    case TextTranslator::TranslatorUtil::da:
    case TextTranslator::TranslatorUtil::nl:
    case TextTranslator::TranslatorUtil::et:
    case TextTranslator::TranslatorUtil::tl:
    case TextTranslator::TranslatorUtil::fi:
    case TextTranslator::TranslatorUtil::gl:
    case TextTranslator::TranslatorUtil::ka:
    case TextTranslator::TranslatorUtil::el:
    case TextTranslator::TranslatorUtil::iw:
    case TextTranslator::TranslatorUtil::hmong:
    case TextTranslator::TranslatorUtil::hu:
    case TextTranslator::TranslatorUtil::is:
    case TextTranslator::TranslatorUtil::lt:
    case TextTranslator::TranslatorUtil::mk:
    case TextTranslator::TranslatorUtil::ms:
    case TextTranslator::TranslatorUtil::mt:
    case TextTranslator::TranslatorUtil::no:
    case TextTranslator::TranslatorUtil::fa:
    case TextTranslator::TranslatorUtil::ro:
    case TextTranslator::TranslatorUtil::sk:
    case TextTranslator::TranslatorUtil::sl:
    case TextTranslator::TranslatorUtil::sw:
    case TextTranslator::TranslatorUtil::sv:
    case TextTranslator::TranslatorUtil::th:
    case TextTranslator::TranslatorUtil::uk:
    case TextTranslator::TranslatorUtil::ur:
    case TextTranslator::TranslatorUtil::cy:
    case TextTranslator::TranslatorUtil::yi:
        return false;
    default:
        break;
    }
    return true;
}

#include "moc_libretranslateengineclient.cpp"
