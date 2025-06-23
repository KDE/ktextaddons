/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later

  based on digikam onlinetranslator code
*/

#include "yandexengineplugin.h"

#include <TextTranslator/TranslatorEngineAccessManager>

#include <KLocalizedString>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrlQuery>

using namespace Qt::Literals::StringLiterals;
QString YandexEnginePlugin::sYandexKey;

YandexEnginePlugin::YandexEnginePlugin(QObject *parent)
    : TextTranslator::TranslatorEnginePlugin(parent)
{
}

YandexEnginePlugin::~YandexEnginePlugin() = default;

void YandexEnginePlugin::translate()
{
    if (sYandexKey.isEmpty()) {
        const QUrl url(u"https://translate.yandex.com"_s);

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

void YandexEnginePlugin::parseCredentials(QNetworkReply *reply)
{
    // Check availability of service
    const QByteArray webSiteData = reply->readAll();
    reply->deleteLater();
    if (webSiteData.isEmpty() || webSiteData.contains("<title>Oops!</title>") || webSiteData.contains("<title>302 Found</title>")) {
        Q_EMIT translateFailed(
            i18n("Error: Engine systems have detected suspicious traffic "
                 "from your computer network. Please try your request again later."));
        return;
    }
    // qCDebug(TRANSLATOR_YANDEX_LOG) << "webSiteData  " << webSiteData;
    const QByteArray sidBeginString = "SID: '";
    const int sidBeginStringPos = webSiteData.indexOf(sidBeginString);

    if (sidBeginStringPos == -1) {
        Q_EMIT translateFailed(i18n("Error: Unable to find Yandex SID in web version."));
        return;
    }

    const int sidBeginPosition = sidBeginStringPos + sidBeginString.size();
    const int sidEndPosition = webSiteData.indexOf('\'', sidBeginPosition);

    if (sidEndPosition == -1) {
        Q_EMIT translateFailed(i18n("Error: Unable to extract Yandex SID from web version."));
        return;
    }

    // Yandex show reversed parts of session ID, need to decode

    const QString sid = QString::fromUtf8(webSiteData.mid(sidBeginPosition, sidEndPosition - sidBeginPosition));

    QStringList sidParts = sid.split(u'.');

    for (int i = 0, total = sidParts.size(); i < total; ++i) {
        std::reverse(sidParts[i].begin(), sidParts[i].end());
    }

    sYandexKey = sidParts.join(u'.');
    translateText();
}

void YandexEnginePlugin::translateText()
{
    if (verifyFromAndToLanguage()) {
        return;
    }

    clear();
    QString lang;
    if (from() == "auto"_L1) {
        lang = languageCode(to());
    } else {
        lang = languageCode(from()) + u'-' + languageCode(to());
    }
    // qDebug() << " lang " << lang;
    // Generate API url
    QUrl url(u"https://translate.yandex.net/api/v1/tr.json/translate"_s);
    QUrlQuery query;
    query.addQueryItem(u"id"_s, sYandexKey + "-2-0"_L1);
    query.addQueryItem(u"srv"_s, u"tr-text"_s);
    query.addQueryItem(u"text"_s, inputText());
    query.addQueryItem(u"lang"_s, lang);
    url.setQuery(query);

    // Setup request
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded"_L1);
    request.setUrl(url);

    // Make reply
    QNetworkReply *reply = TextTranslator::TranslatorEngineAccessManager::self()->networkManager()->post(request, QByteArray());
    connect(reply, &QNetworkReply::errorOccurred, this, [this, reply](QNetworkReply::NetworkError error) {
        slotError(error);
        reply->deleteLater();
    });

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        reply->deleteLater();
        parseTranslation(reply);
    });
}

void YandexEnginePlugin::parseTranslation(QNetworkReply *reply)
{
    const QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    if (hasDebug()) {
        setJsonDebug(QString::fromUtf8(jsonResponse.toJson(QJsonDocument::Indented)));
    }
    const QJsonObject jsonData = jsonResponse.object();
    reply->deleteLater();

    // Parse language
    if (from() == "auto"_L1) {
        QString sourceCode = jsonData.value(u"lang"_s).toString();
        sourceCode = sourceCode.left(sourceCode.indexOf(u'-'));
        qDebug() << " sourceCode " << sourceCode;
    }

    // qDebug() << "jsonData  " << jsonData;
    appendResult(jsonData.value(u"text"_s).toArray().at(0).toString());
    Q_EMIT translateDone();
}

QString YandexEnginePlugin::languageCode(const QString &langStr)
{
    if (langStr == "zh"_L1) {
        return u"zn"_s;
    } else if (langStr == "ja"_L1) {
        return u"jv"_s;
    }
    return langStr;
}

#include "moc_yandexengineplugin.cpp"
