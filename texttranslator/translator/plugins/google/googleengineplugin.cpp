/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "googleengineplugin.h"

#include "googletranslator_debug.h"
#include <KLocalizedString>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QRegularExpression>
#include <QUrlQuery>
#include <TextTranslator/TranslatorEngineAccessManager>

using namespace Qt::Literals::StringLiterals;
GoogleEnginePlugin::GoogleEnginePlugin(QObject *parent)
    : TextTranslator::TranslatorEnginePlugin(parent)
{
    connect(TextTranslator::TranslatorEngineAccessManager::self()->networkManager(),
            &QNetworkAccessManager::finished,
            this,
            &GoogleEnginePlugin::slotTranslateFinished);
}

GoogleEnginePlugin::~GoogleEnginePlugin() = default;

void GoogleEnginePlugin::translate()
{
    if (verifyFromAndToLanguage()) {
        return;
    }

    clear();

    QUrlQuery urlQuery;
    urlQuery.addQueryItem(u"client"_s, u"gtx"_s);
    urlQuery.addQueryItem(u"sl"_s, languageCode(from()));
    urlQuery.addQueryItem(u"tl"_s, languageCode(to()));
    urlQuery.addQueryItem(u"dt"_s, u"t"_s);
    urlQuery.addQueryItem(u"q"_s, inputText());

    QUrl url;
    url.setQuery(urlQuery);
    url.setScheme(u"https"_s);
    url.setHost(u"translate.googleapis.com"_s);
    url.setPath(u"/translate_a/single"_s);
    const QNetworkRequest request(url);

    QNetworkReply *reply = TextTranslator::TranslatorEngineAccessManager::self()->networkManager()->get(request);
    connect(reply, &QNetworkReply::errorOccurred, this, [this, reply](QNetworkReply::NetworkError error) {
        slotError(error);
        reply->deleteLater();
    });
}

QString GoogleEnginePlugin::languageCode(const QString &langStr)
{
    if (langStr == "iw"_L1) {
        return u"iw"_s;
    }
    return langStr;
}

void GoogleEnginePlugin::slotTranslateFinished(QNetworkReply *reply)
{
    clear();
    mJsonData = QString::fromUtf8(reply->readAll());
    reply->deleteLater();
    //  jsonData contains arrays like this: ["foo",,"bar"]
    //  but this is not valid JSON for QJSON, it expects empty strings: ["foo","","bar"]
    mJsonData.replace(QRegularExpression(u",{3,3}"_s), u",\"\",\"\","_s);
    mJsonData.replace(QRegularExpression(u",{2,2}"_s), u",\"\","_s);
    qCDebug(TRANSLATOR_GOOGLE_LOG) << mJsonData;

    QJsonParseError parsingError;
    const QJsonDocument jsonDoc = QJsonDocument::fromJson(mJsonData.toUtf8(), &parsingError);
    if (parsingError.error != QJsonParseError::NoError || jsonDoc.isNull()) {
        Q_EMIT translateFailed(i18n("Invalid answer."));
        return;
    }
    const QVariantList json = jsonDoc.toVariant().toList();
    if (hasDebug()) {
        setJsonDebug(QString::fromUtf8(jsonDoc.toJson(QJsonDocument::Indented)));
    }
    for (const QVariant &level0 : json) {
        const QVariantList listLevel0 = level0.toList();
        if (listLevel0.isEmpty()) {
            continue;
        }
        for (const QVariant &level1 : listLevel0) {
            if (level1.toList().size() <= 2) {
                continue;
            }
            appendResult(level1.toList().at(0).toString());
        }
    }
    Q_EMIT translateDone();
}
