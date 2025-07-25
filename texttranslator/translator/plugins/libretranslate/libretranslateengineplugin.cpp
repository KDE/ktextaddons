/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later

  based on digikam onlinetranslator code

*/

#include "libretranslateengineplugin.h"

#include "libretranslateengineutil.h"
#include "libretranslatetranslator_debug.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QJsonDocument>
#include <QJsonObject>
#include <TextTranslator/TranslatorEngineAccessManager>
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

    QByteArray postData = "&q=" + QUrl::toPercentEncoding(inputText()) + "&source=" + from().toUtf8() + "&target=" + to().toUtf8();
    if (!mApiKey.isEmpty()) {
        postData += "&api_key=" + mApiKey.toUtf8();
    }
    const auto url = QUrl(u"%1/translate"_s.arg(mServerUrl));
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded"_L1);
    request.setUrl(url);

    qCDebug(TRANSLATOR_LIBRETRANSLATE_LOG) << " url " << url;

    QNetworkReply *reply = TextTranslator::TranslatorEngineAccessManager::self()->networkManager()->post(request, postData);
    connect(reply, &QNetworkReply::errorOccurred, this, [this, reply](QNetworkReply::NetworkError error) {
        slotError(error);
        reply->deleteLater();
    });
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        reply->deleteLater();
        parseTranslation(reply);
    });
}

void LibreTranslateEnginePlugin::parseTranslation(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        Q_EMIT translateFailed(reply->errorString());
        reply->deleteLater();
        return;
    }
    const QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    if (hasDebug()) {
        setJsonDebug(QString::fromUtf8(jsonResponse.toJson(QJsonDocument::Indented)));
    }

    const QJsonObject responseObject = jsonResponse.object();
    setResult(responseObject.value(u"translatedText"_s).toString());
    reply->deleteLater();
    qCDebug(TRANSLATOR_LIBRETRANSLATE_LOG) << " result " << result();
    Q_EMIT translateDone();
}

void LibreTranslateEnginePlugin::loadSettings()
{
    KConfigGroup myGroup(KSharedConfig::openConfig(), LibreTranslateEngineUtil::groupName());
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
