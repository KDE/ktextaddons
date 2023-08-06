/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "downloadlanguagejob.h"
#include "bergamotengineutils.h"
#include "extractlanguagejob.h"
#include "libbergamot_debug.h"
#include <KLocalizedString>
#include <QFileInfo>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTemporaryFile>
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
    mDestination = new QTemporaryFile(this);
    if (!mDestination->open()) {
        Q_EMIT errorText(i18n("Cannot open file for downloading."));
        deleteLater();
        return;
    }

    QNetworkRequest request(mUrl);
    qDebug() << " mUrl " << mUrl;
    QNetworkReply *reply = TextTranslator::TranslatorEngineAccessManager::self()->networkManager()->get(request);
    connect(reply, &QNetworkReply::errorOccurred, this, [this, reply](QNetworkReply::NetworkError error) {
        if (error == QNetworkReply::ServiceUnavailableError) {
            Q_EMIT errorText(i18n("Error: Engine systems have detected suspicious traffic from your computer network. Please try your request again later."));
        } else {
            Q_EMIT errorText(i18n("Impossible to access to url: %1", mUrl.toString()));
        }
        reply->deleteLater();
    });

    connect(reply, &QNetworkReply::downloadProgress, this, &DownloadLanguageJob::downloadProgress);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        mDestination->flush();
        mDestination->seek(0);
        reply->deleteLater();
        extractLanguage();
    });
    connect(reply, &QIODevice::readyRead, this, [=] {
        const QByteArray buffer = reply->readAll();
        if (mDestination->write(buffer) == -1) {
            Q_EMIT errorText(i18n("Error during writing on disk: %1", mDestination->errorString()));
            reply->abort();
        }
    });
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
    qDebug() << " void DownloadLanguageJob::extractLanguage()" << mDestination->fileName();
    auto extraJob = new ExtractLanguageJob(this);
    extraJob->setSource(mDestination->fileName());
    const QFileInfo info(mUrl.toString());
    const QString baseName = info.baseName();
    extraJob->setTarget(BergamotEngineUtils::storageLanguagePath() + QLatin1Char('/') + baseName);
    connect(extraJob, &ExtractLanguageJob::errorText, this, &DownloadLanguageJob::errorText);
    connect(extraJob, &ExtractLanguageJob::finished, this, &DownloadLanguageJob::extractDone);

    extraJob->start();
}

void DownloadLanguageJob::slotExtractDone()
{
    Q_EMIT extractDone();
    deleteLater();
}

#include "moc_downloadlanguagejob.cpp"
