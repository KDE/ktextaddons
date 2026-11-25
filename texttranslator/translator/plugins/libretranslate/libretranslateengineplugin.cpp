/*
  SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later

  based on digikam onlinetranslator code

*/

#include "libretranslateengineplugin.h"

#include "libretranslateengineutil.h"
#include "libretranslatetextjob.h"
#include "libretranslatetranslator_debug.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <qt6keychain/keychain.h>

using namespace Qt::Literals::StringLiterals;
LibreTranslateEnginePlugin::LibreTranslateEnginePlugin(QObject *parent)
    : TextTranslator::TranslatorEnginePlugin(parent)
{
    loadSettings();
}

LibreTranslateEnginePlugin::~LibreTranslateEnginePlugin() = default;

void LibreTranslateEnginePlugin::translate()
{
    if (verifyFromAndToLanguage()) {
        return;
    }
    if (mServerUrl.isEmpty()) {
        Q_EMIT translateFailed(i18n("Server url is not defined."));
        return;
    }
    if (mRequiredApiKey && mApiKey.isEmpty()) {
        Q_EMIT translateFailed(i18n("Server needs Api Key."));
        return;
    }
    translateText();
}

void LibreTranslateEnginePlugin::slotConfigureChanged()
{
    loadSettings();
}

void LibreTranslateEnginePlugin::translateText()
{
    clear();

    auto job = new LibreTranslateTextJob(this);
    job->setInfo({
        .serverUrl = mServerUrl,
        .apiKey = mApiKey,
        .inputText = inputText(),
        .from = from(),
        .to = to(),
        .hasDebug = hasDebug(),
    });
    connect(job, &LibreTranslateTextJob::networkError, this, &LibreTranslateEnginePlugin::slotError);
    connect(job, &LibreTranslateTextJob::translateFailed, this, &LibreTranslateEnginePlugin::translateFailed);
    connect(job, &LibreTranslateTextJob::translateDone, this, [this](const QString &result, const QString &jsonDebug) {
        if (hasDebug()) {
            setJsonDebug(jsonDebug);
        }
        setResult(result);
        Q_EMIT translateDone();
    });
    job->start();
}

void LibreTranslateEnginePlugin::loadSettings()
{
    const KConfigGroup myGroup(KSharedConfig::openConfig(), LibreTranslateEngineUtil::groupName());
    mServerUrl = myGroup.readEntry(LibreTranslateEngineUtil::serverUrlKey(), LibreTranslateEngineUtil::defaultServerUrl());
    // Fallback
    if (mServerUrl.isEmpty()) {
        mServerUrl = LibreTranslateEngineUtil::defaultServerUrl();
    }
    mServerUrl = LibreTranslateEngineUtil::adaptUrl(mServerUrl);
    mRequiredApiKey = myGroup.readEntry(LibreTranslateEngineUtil::serverRequiredApiKey(), false);

    auto readJob = new QKeychain::ReadPasswordJob(LibreTranslateEngineUtil::translatorGroupName(), this);
    connect(readJob, &QKeychain::Job::finished, this, &LibreTranslateEnginePlugin::slotApiKeyRead);
    readJob->setKey(LibreTranslateEngineUtil::apiGroupName());
    readJob->start();
}

void LibreTranslateEnginePlugin::slotApiKeyRead(QKeychain::Job *baseJob)
{
    auto job = qobject_cast<QKeychain::ReadPasswordJob *>(baseJob);
    Q_ASSERT(job);
    if (!job->error()) {
        mApiKey = job->textData();
    } else {
        qCWarning(TRANSLATOR_LIBRETRANSLATE_LOG) << "We have an error during reading password " << job->errorString();
    }
}

#include "moc_libretranslateengineplugin.cpp"
