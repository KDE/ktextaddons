/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "downloadlanguagejob.h"
#include "extractlanguagejob.h"
#include "generateinstalledlanguageinfojob.h"
#include "libvoskspeechtotext_debug.h"
#include "speechtotext/speechtotextengineaccessmanager.h"
#include <KLocalizedString>
#include <QFileInfo>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTemporaryFile>

DownloadLanguageJob::DownloadLanguageJob(QObject *parent)
    : QObject{parent}
{
}

DownloadLanguageJob::~DownloadLanguageJob()
{
    delete mHash;
}

void DownloadLanguageJob::start()
{
    if (!canStart()) {
        qCWarning(LIBVOSKSPEECHTOTEXT_LOG) << "Impossible to start DownloadLanguageJob";
        deleteLater();
        return;
    }
    mDestination = new QTemporaryFile(this);
    if (!mDestination->open()) {
        Q_EMIT errorText(i18n("Cannot open file for downloading."));
        delete mDestination;
        deleteLater();
        return;
    }

    mHash = new QCryptographicHash(QCryptographicHash::Md5);

    QNetworkRequest request(mInfo.url);
    // qDebug() << " mInfo.url " << mInfo.url;
    QNetworkReply *reply = TextSpeechToText::SpeechToTextEngineAccessManager::self()->networkManager()->get(request);
    connect(reply, &QNetworkReply::errorOccurred, this, [this](QNetworkReply::NetworkError error) {
        if (error == QNetworkReply::ServiceUnavailableError) {
            Q_EMIT errorText(i18n("Error: Engine systems have detected suspicious traffic from your computer network. Please try your request again later."));
        } else {
            Q_EMIT errorText(i18n("Impossible to access to url: %1", mInfo.url.toString()));
        }
    });

    connect(reply, &QNetworkReply::downloadProgress, this, &DownloadLanguageJob::downloadProgress);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        mDestination->flush();
        mDestination->seek(0);
        reply->deleteLater();
        if (!mInfo.checksum.isEmpty() && mHash->result().toHex() != mInfo.checksum.toLatin1()) {
            // qDebug() << " mHash->result() " << mHash->result().toHex() << " mCheckSum " << mCheckSum;
            Q_EMIT errorText(i18n("CheckSum is not correct."));
            deleteLater();
            return;
        } else {
            extractLanguage();
        }
    });
    connect(reply, &QIODevice::readyRead, this, [this, reply] {
        const QByteArray buffer = reply->readAll();
        if (mDestination->write(buffer) == -1) {
            Q_EMIT errorText(i18n("Error during writing on disk: %1", mDestination->errorString()));
            reply->abort();
        }
        mHash->addData(buffer);
    });
}

bool DownloadLanguageJob::canStart() const
{
    return mInfo.isValid();
}

void DownloadLanguageJob::extractLanguage()
{
    auto extraJob = new ExtractLanguageJob(this);
    extraJob->setSource(mDestination->fileName());
    connect(extraJob, &ExtractLanguageJob::errorText, this, &DownloadLanguageJob::errorText);
    connect(extraJob, &ExtractLanguageJob::finished, this, &DownloadLanguageJob::generateInstalledLanguageInfo);

    extraJob->start();
}

void DownloadLanguageJob::generateInstalledLanguageInfo()
{
    auto generateInstalledLanguageJob = new GenerateInstalledLanguageInfoJob(this);
    GenerateInstalledLanguageInfoJob::LanguageInfo info;
    info.pathToStore = VoskEngineUtils::storageLanguagePath() + QLatin1Char('/') + mInfo.name;
    info.info.absoluteLanguageModelPath = VoskEngineUtils::storageLanguagePath() + QLatin1Char('/') + mInfo.name;
    info.info.name = mInfo.name;
    info.info.url = mInfo.url.toString();
    info.info.versionStr = mInfo.version;
    generateInstalledLanguageJob->setInfo(info);

    connect(generateInstalledLanguageJob, &GenerateInstalledLanguageInfoJob::errorText, this, &DownloadLanguageJob::errorText);
    connect(generateInstalledLanguageJob, &GenerateInstalledLanguageInfoJob::generatedDone, this, &DownloadLanguageJob::slotGenerateInstalledLanguageInfoDone);
    generateInstalledLanguageJob->start();
}

void DownloadLanguageJob::slotGenerateInstalledLanguageInfoDone()
{
    Q_EMIT extractDone();
    deleteLater();
}

DownloadLanguageJob::DownloadLanguageInfo DownloadLanguageJob::info() const
{
    return mInfo;
}

void DownloadLanguageJob::setInfo(const DownloadLanguageInfo &newInfo)
{
    mInfo = newInfo;
}

QDebug operator<<(QDebug d, const DownloadLanguageJob::DownloadLanguageInfo &t)
{
    d << "url " << t.url;
    d << "checksum " << t.checksum;
    d << "name " << t.name;
    d << "version " << t.version;
    return d;
}

bool DownloadLanguageJob::DownloadLanguageInfo::isValid() const
{
    return !url.isEmpty() && !name.isEmpty();
}

#include "moc_downloadlanguagejob.cpp"
