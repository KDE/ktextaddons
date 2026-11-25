/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "libretranslatetextjob.h"
#include "libretranslatetranslator_debug.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <TextTranslator/TranslatorEngineAccessManager>

using namespace Qt::Literals::StringLiterals;

LibreTranslateTextJob::LibreTranslateTextJob(QObject *parent)
    : QObject{parent}
{
}

LibreTranslateTextJob::~LibreTranslateTextJob() = default;

bool LibreTranslateTextJob::canStart() const
{
    return mInfo.isValid();
}

void LibreTranslateTextJob::start()
{
    if (!canStart()) {
        qCWarning(TRANSLATOR_LIBRETRANSLATE_LOG) << "Impossible to start LibreTranslateTextJob";
        deleteLater();
        return;
    }

    QByteArray postData = "&q=" + QUrl::toPercentEncoding(mInfo.inputText) + "&source=" + mInfo.from.toUtf8() + "&target=" + mInfo.to.toUtf8();
    if (!mInfo.apiKey.isEmpty()) {
        postData += "&api_key=" + mInfo.apiKey.toUtf8();
    }
    const auto url = QUrl(u"%1/translate"_s.arg(mInfo.serverUrl));
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded"_L1);
    request.setUrl(url);

    qCDebug(TRANSLATOR_LIBRETRANSLATE_LOG) << " url " << url;

    QNetworkReply *reply = TextTranslator::TranslatorEngineAccessManager::self()->networkManager()->post(request, postData);
    connect(reply, &QNetworkReply::errorOccurred, this, [this](QNetworkReply::NetworkError error) {
        Q_EMIT networkError(error);
    });
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        reply->deleteLater();
        parseTranslation(reply);
        deleteLater();
    });
}

void LibreTranslateTextJob::parseTranslation(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        Q_EMIT translateFailed(reply->errorString());
        return;
    }
    const QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    QString jsonDebug;
    if (mInfo.hasDebug) {
        jsonDebug = QString::fromUtf8(jsonResponse.toJson(QJsonDocument::Indented));
    }

    const QJsonObject responseObject = jsonResponse.object();
    const QString result = responseObject.value(u"translatedText"_s).toString();
    qCDebug(TRANSLATOR_LIBRETRANSLATE_LOG) << " result " << result;
    Q_EMIT translateDone(result, jsonDebug);
}

LibreTranslateTextJob::LibreTranslateTextInfo LibreTranslateTextJob::info() const
{
    return mInfo;
}

void LibreTranslateTextJob::setInfo(const LibreTranslateTextInfo &newInfo)
{
    mInfo = newInfo;
}

bool LibreTranslateTextJob::LibreTranslateTextInfo::isValid() const
{
    return !serverUrl.isEmpty() && !inputText.isEmpty() && !from.isEmpty() && !to.isEmpty();
}

#include "moc_libretranslatetextjob.cpp"
