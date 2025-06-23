/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later

  based on digikam onlinetranslator code
*/

#include "bingengineplugin.h"

#include "translator/plugins/bing/bingtranslator_debug.h"
#include <KLocalizedString>
#include <QCoreApplication>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <TextTranslator/TranslatorEngineAccessManager>

using namespace Qt::Literals::StringLiterals;
QByteArray BingEnginePlugin::sBingKey;
QByteArray BingEnginePlugin::sBingToken;
QString BingEnginePlugin::sBingIg;
QString BingEnginePlugin::sBingIid;

BingEnginePlugin::BingEnginePlugin(QObject *parent)
    : TextTranslator::TranslatorEnginePlugin(parent)
{
}

BingEnginePlugin::~BingEnginePlugin() = default;

void BingEnginePlugin::translate()
{
    if (sBingKey.isEmpty() || sBingToken.isEmpty()) {
        const QUrl url(u"https://www.bing.com/translator"_s);
        QNetworkReply *reply = TextTranslator::TranslatorEngineAccessManager::self()->networkManager()->get(QNetworkRequest(url));
        connect(reply, &QNetworkReply::finished, this, [this, reply]() {
            parseCredentials(reply);
        });
        connect(reply, &QNetworkReply::errorOccurred, this, [this, reply](QNetworkReply::NetworkError error) {
            slotError(error);
            reply->deleteLater();
        });
    } else {
        translateText();
    }
}

void BingEnginePlugin::parseCredentials(QNetworkReply *reply)
{
    const QByteArray webSiteData = reply->readAll();
    reply->deleteLater();
    const QByteArray credentialsBeginString = QByteArrayLiteral("var params_RichTranslateHelper = [");
    const int credentialsBeginPos = webSiteData.indexOf(credentialsBeginString);

    if (credentialsBeginPos == -1) {
        Q_EMIT translateFailed(i18n("Error: Unable to find Bing credentials in web version."));
        return;
    }

    const int keyBeginPos = credentialsBeginPos + credentialsBeginString.size();
    const int keyEndPos = webSiteData.indexOf(',', keyBeginPos);

    if (keyEndPos == -1) {
        Q_EMIT translateFailed(i18n("Error: Unable to extract Bing key from web version."));
        return;
    }

    sBingKey = webSiteData.mid(keyBeginPos, keyEndPos - keyBeginPos);
    const int tokenBeginPos = keyEndPos + 2; // Skip two symbols instead of one because the value is enclosed in quotes
    const int tokenEndPos = webSiteData.indexOf('"', tokenBeginPos);

    if (tokenEndPos == -1) {
        Q_EMIT translateFailed(i18n("Error: Unable to extract Bing token from web version."));
        return;
    }

    sBingToken = webSiteData.mid(tokenBeginPos, tokenEndPos - tokenBeginPos);
    const int igBeginPos = webSiteData.indexOf("IG");
    const int igEndPos = webSiteData.indexOf('"', igBeginPos + 2);

    if (igEndPos == -1) {
        Q_EMIT translateFailed(i18n("Error: Unable to extract additional Bing information from web version."));
        return;
    }

    sBingIg = QString::fromUtf8(webSiteData.mid(igBeginPos, igEndPos - igBeginPos));
    const int iidBeginPos = webSiteData.indexOf("data-iid");
    const int iidEndPos = webSiteData.indexOf('"', iidBeginPos + 2);

    if (iidEndPos == -1) {
        Q_EMIT translateFailed(i18n("Error: Unable to extract additional Bing information from web version."));
        return;
    }

    sBingIid = QString::fromUtf8(webSiteData.mid(iidBeginPos, iidEndPos - iidBeginPos));

    // qCDebug(TRANSLATOR_BING_LOG) << "sBingIid " << sBingIid << " sBingIg " << sBingIg << " sBingToken " << sBingToken << " sBingKey " << sBingKey;
    translateText();
}

void BingEnginePlugin::translateText()
{
    if (verifyFromAndToLanguage()) {
        return;
    }
    clear();

    const QByteArray postData = "&text=" + QUrl::toPercentEncoding(inputText()) + "&fromLang=" + languageCode(from()).toUtf8()
        + "&to=" + languageCode(to()).toUtf8() + "&token=" + sBingToken + "&key=" + sBingKey;

    qCDebug(TRANSLATOR_BING_LOG) << " postData " << postData;
    QUrl url(u"https://www.bing.com/ttranslatev3"_s);
    url.setQuery(u"IG=%1&IID=%2"_s.arg(sBingIg, sBingIid));
    qCDebug(TRANSLATOR_BING_LOG) << " url " << url;

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded"_L1);
    request.setHeader(QNetworkRequest::UserAgentHeader, u"%1/%2"_s.arg(QCoreApplication::applicationName(), QCoreApplication::applicationVersion()));

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

void BingEnginePlugin::parseTranslation(QNetworkReply *reply)
{
    // Parse translation data
    const QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    qCDebug(TRANSLATOR_BING_LOG) << " jsonResponse " << jsonResponse;
    const QJsonObject responseObject = jsonResponse.array().first().toObject();
    if (from() == "auto"_L1) {
        const QString langCode = responseObject.value(u"detectedLanguage"_s).toObject().value(u"language"_s).toString();
        setFrom(langCode);
        //        if (m_sourceLang == NoLanguage)
        //        {
        //            resetData(ParsingError, i18n("Error: Unable to parse autodetected language"));
        //            return;
        //        }
    }

    const QJsonObject translationsObject = responseObject.value(u"translations"_s).toArray().first().toObject();
    appendResult(translationsObject.value(u"text"_s).toString());
    if (hasDebug()) {
        setJsonDebug(QString::fromUtf8(jsonResponse.toJson(QJsonDocument::Indented)));
    }

    qCDebug(TRANSLATOR_BING_LOG) << " mResult " << result();
    // m_translationTranslit               += translationsObject.value(u"transliteration"_s).toObject().value(u"text"_s).toString();
    reply->deleteLater();
    Q_EMIT translateDone();
}

QString BingEnginePlugin::languageCode(const QString &langStr)
{
    if (langStr == "auto"_L1) {
        return u"auto-detect"_s;
    } else if (langStr == "sr"_L1) {
        return u"sr-Cyrl"_s;
    } else if (langStr == "bs"_L1) {
        return u"bs-Latn"_s;
    } else if (langStr == "hmn"_L1) {
        return u"mww"_s;
    } else if (langStr == "zh"_L1) {
        return u"zh-Hans"_s;
    } else if (langStr == "zt"_L1) {
        return u"zh-Hant"_s;
    }
    return langStr;
}

#include "moc_bingengineplugin.cpp"
