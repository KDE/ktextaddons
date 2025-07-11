/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later

  based on digikam onlinetranslator code

*/

#include "lingvaengineplugin.h"

#include "lingvaengineutil.h"
#include "lingvatranslator_debug.h"
#include <TextTranslator/TranslatorEngineAccessManager>

#include <KConfigGroup>
#include <KSharedConfig>

#include <QJsonDocument>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
LingvaEnginePlugin::LingvaEnginePlugin(QObject *parent)
    : TextTranslator::TranslatorEnginePlugin(parent)
{
    loadSettings();
}

LingvaEnginePlugin::~LingvaEnginePlugin() = default;

void LingvaEnginePlugin::translate()
{
    if (verifyFromAndToLanguage()) {
        return;
    }
    translateText();
}

void LingvaEnginePlugin::translateText()
{
    clear();

    const QUrl url(u"%1/api/v1/%2/%3/%4"_s.arg(mServerUrl, languageCode(from()), languageCode(to()), QString::fromUtf8(QUrl::toPercentEncoding(inputText()))));

    qCDebug(TRANSLATOR_LINGVA_LOG) << " url " << url;
    const QNetworkRequest request(url);

    QNetworkReply *reply = TextTranslator::TranslatorEngineAccessManager::self()->networkManager()->get(request);
    connect(reply, &QNetworkReply::errorOccurred, this, [this, reply](QNetworkReply::NetworkError error) {
        slotError(error);
        reply->deleteLater();
    });
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        reply->deleteLater();
        parseTranslation(reply);
    });
}

void LingvaEnginePlugin::parseTranslation(QNetworkReply *reply)
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
    setResult(responseObject.value(u"translation"_s).toString());
    reply->deleteLater();
    qCDebug(TRANSLATOR_LINGVA_LOG) << " result " << result();
    Q_EMIT translateDone();
}

void LingvaEnginePlugin::loadSettings()
{
    KConfigGroup myGroup(KSharedConfig::openConfig(), LingvaEngineUtil::groupName());
    mServerUrl = myGroup.readEntry(LingvaEngineUtil::serverUrlKey(), LingvaEngineUtil::defaultServerUrl());
}

void LingvaEnginePlugin::slotConfigureChanged()
{
    loadSettings();
}

QString LingvaEnginePlugin::languageCode(const QString &langStr)
{
    if (langStr == "zh"_L1) {
        return u"zh"_s;
    } else if (langStr == "zt"_L1) {
        return u"zh_HANT"_s;
    }
    return langStr;
}

#include "moc_lingvaengineplugin.cpp"
