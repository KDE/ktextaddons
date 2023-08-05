/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "downloadlanguagejob.h"
#include "extractlanguagejob.h"
#include "libbergamot_debug.h"
#include <KLocalizedString>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <TextTranslator/TranslatorEngineAccessManager>

DownloadLanguageJob::DownloadLanguageJob(QObject *parent)
    : QObject{parent}
{
}

DownloadLanguageJob::~DownloadLanguageJob() = default;

void DownloadLanguageJob::start()
{
    if (!canStart()) {
        qCWarning(TRANSLATOR_LIBBERGAMOT_LOG) << "Impossible to start DownloadLanguageJob";
        deleteLater();
        return;
    }
    QNetworkRequest request(mUrl);
    QNetworkReply *reply = TextTranslator::TranslatorEngineAccessManager::self()->networkManager()->get(request);
    connect(reply, &QNetworkReply::errorOccurred, this, [this, reply](QNetworkReply::NetworkError error) {
        if (error == QNetworkReply::ServiceUnavailableError) {
            Q_EMIT i18n("Error: Engine systems have detected suspicious traffic from your computer network. Please try your request again later.");
        } else {
            Q_EMIT errorText(i18n("Impossible to access to url: %1", mUrl.toString()));
        }
        reply->deleteLater();
    });

    connect(reply, &QNetworkReply::downloadProgress, this, &DownloadLanguageJob::downloadProgress);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        reply->deleteLater();
        // parseTranslation(reply);
    });
    connect(reply, &QIODevice::readyRead, this, [=] {
        QByteArray buffer = reply->readAll();
        // TODO
    });
    // TODO
}

bool DownloadLanguageJob::canStart() const
{
    return !mUrl.isEmpty();
}

QUrl DownloadLanguageJob::url() const
{
    return mUrl;
}

void DownloadLanguageJob::setUrl(const QUrl &newUrl)
{
    mUrl = newUrl;
}

void DownloadLanguageJob::extractLanguage()
{
    auto extraJob = new ExtractLanguageJob(this);
    // TODO add source/target
    connect(extraJob, &ExtractLanguageJob::errorText, this, &DownloadLanguageJob::errorText);
    connect(extraJob, &ExtractLanguageJob::finished, this, &DownloadLanguageJob::extractDone);

    extraJob->start();
}

#include "moc_downloadlanguagejob.cpp"
