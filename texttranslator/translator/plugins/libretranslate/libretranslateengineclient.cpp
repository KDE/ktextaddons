/*
  SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "libretranslateengineclient.h"

#include "libretranslateengineconfiguredialog.h"
#include "libretranslateengineplugin.h"
#include "libretranslateengineutil.h"
#include "libretranslatelanguagesjob.h"
#include "libretranslatetranslator_debug.h"
#include "translator/misc/translatorutil.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QPointer>
#include <optional>
#include <qt6keychain/keychain.h>

using namespace Qt::Literals::StringLiterals;
namespace
{
// Don't use TranslatorUtil::stringToLanguage(): it falls back to English for unknown codes
std::optional<TextTranslator::TranslatorUtil::Language> codeToLanguage(const QString &code)
{
    for (int i = TextTranslator::TranslatorUtil::Language::automatic + 1; i <= TextTranslator::TranslatorUtil::Language::lastLanguage; ++i) {
        if (const auto language = static_cast<TextTranslator::TranslatorUtil::Language>(i); TextTranslator::TranslatorUtil::languageCode(language) == code) {
            return language;
        }
    }
    return std::nullopt;
}
}

LibreTranslateEngineClient::LibreTranslateEngineClient(QObject *parent)
    : TextTranslator::TranslatorEngineClient{parent}
{
    // Server url can change: reload the languages list
    connect(this, &LibreTranslateEngineClient::configureChanged, this, &LibreTranslateEngineClient::resetLanguages);
}

LibreTranslateEngineClient::~LibreTranslateEngineClient() = default;

QString LibreTranslateEngineClient::name() const
{
    return u"libretranslate"_s;
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
    loadLanguages();
    // Use the static list until the server answered
    if (mFromLanguages.isEmpty()) {
        mFromLanguages = fillLanguages();
    }
    return mFromLanguages;
}

QMap<TextTranslator::TranslatorUtil::Language, QString> LibreTranslateEngineClient::supportedToLanguages()
{
    if (mLanguageTargets.isEmpty()) {
        return supportedFromLanguages();
    }
    return mToLanguages;
}

void LibreTranslateEngineClient::generateToListFromCurrentToLanguage(const QString &languageCode)
{
    mLanguageCode = languageCode;
    loadLanguages();
    updateToLanguageList();
}

QString LibreTranslateEngineClient::serverUrl()
{
    const KConfigGroup myGroup(KSharedConfig::openConfig(), LibreTranslateEngineUtil::groupName());
    QString url = myGroup.readEntry(LibreTranslateEngineUtil::serverUrlKey(), LibreTranslateEngineUtil::defaultServerUrl());
    if (url.isEmpty()) {
        url = LibreTranslateEngineUtil::defaultServerUrl();
    }
    return LibreTranslateEngineUtil::adaptUrl(url);
}

void LibreTranslateEngineClient::loadLanguages()
{
    if (mLanguagesRequested) {
        return;
    }
    mLanguagesRequested = true;
    const QString url = serverUrl();
    auto job = new LibreTranslateLanguagesJob(this);
    job->setInfo({.serverUrl = url});
    connect(job, &LibreTranslateLanguagesJob::getLanguagesDone, this, [this, url](const QMap<QString, QStringList> &languages) {
        slotLanguagesLoaded(url, languages);
    });
    connect(job, &LibreTranslateLanguagesJob::getLanguagesFailed, this, [](const QString &errorStr) {
        qCWarning(TRANSLATOR_LIBRETRANSLATE_LOG) << "Impossible to get languages list:" << errorStr;
    });
    job->start();
}

void LibreTranslateEngineClient::slotLanguagesLoaded(const QString &url, const QMap<QString, QStringList> &languages)
{
    if (url != serverUrl()) {
        // Server changed while the job was running
        return;
    }
    mLanguageTargets = languages;
    mFromLanguages.clear();
    const auto automatic = TextTranslator::TranslatorUtil::automatic;
    mFromLanguages.insert(automatic, TextTranslator::TranslatorUtil::translatedLanguage(automatic));
    for (const auto &[code, targets] : mLanguageTargets.asKeyValueRange()) {
        if (const auto language = codeToLanguage(code); language.has_value()) {
            mFromLanguages.insert(*language, TextTranslator::TranslatorUtil::translatedLanguage(*language));
        }
    }
    updateToLanguageList();
    Q_EMIT languagesChanged();
}

void LibreTranslateEngineClient::updateToLanguageList()
{
    mToLanguages.clear();
    const auto addTargets = [this](const QStringList &targets) {
        for (const QString &code : targets) {
            if (const auto language = codeToLanguage(code); language.has_value()) {
                mToLanguages.insert(*language, TextTranslator::TranslatorUtil::translatedLanguage(*language));
            }
        }
    };
    // "auto" or unknown source: offer every target supported by the server
    if (const auto it = mLanguageTargets.constFind(mLanguageCode); it != mLanguageTargets.cend()) {
        addTargets(*it);
    } else {
        for (const QStringList &targets : std::as_const(mLanguageTargets)) {
            addTargets(targets);
        }
    }
}

void LibreTranslateEngineClient::resetLanguages()
{
    mLanguageTargets.clear();
    mFromLanguages.clear();
    mToLanguages.clear();
    mLanguagesRequested = false;
    Q_EMIT languagesChanged();
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
    readJob->setKey(LibreTranslateEngineUtil::apiGroupName());
    readJob->start();
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
