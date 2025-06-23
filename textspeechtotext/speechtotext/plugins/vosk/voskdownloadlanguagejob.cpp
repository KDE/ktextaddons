/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskdownloadlanguagejob.h"
using namespace Qt::Literals::StringLiterals;

#include "generateinstalledlanguageinfojob.h"
#include "libvoskspeechtotext_debug.h"
#include "speechtotext/speechtotextengineaccessmanager.h"
#include "voskextractlanguagejob.h"
#include <KLocalizedString>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTemporaryFile>

VoskDownloadLanguageJob::VoskDownloadLanguageJob(QObject *parent)
    : QObject{parent}
{
}

VoskDownloadLanguageJob::~VoskDownloadLanguageJob()
{
    delete mHash;
}

void VoskDownloadLanguageJob::start()
{
    if (!canStart()) {
        qCWarning(LIBVOSKSPEECHTOTEXT_LOG) << "Impossible to start DownloadLanguageJob";
        deleteLater();
        return;
    }
    mDestination = new QTemporaryFile(this);
    if (!mDestination->open()) {
        Q_EMIT errorText(i18n("Cannot open file for downloading."));
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

    connect(reply, &QNetworkReply::downloadProgress, this, &VoskDownloadLanguageJob::downloadProgress);
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

bool VoskDownloadLanguageJob::canStart() const
{
    return mInfo.isValid();
}

void VoskDownloadLanguageJob::extractLanguage()
{
    auto extraJob = new VoskExtractLanguageJob(this);
    extraJob->setSource(mDestination->fileName());
    connect(extraJob, &VoskExtractLanguageJob::errorText, this, &VoskDownloadLanguageJob::errorText);
    connect(extraJob, &VoskExtractLanguageJob::finished, this, &VoskDownloadLanguageJob::generateInstalledLanguageInfo);

    extraJob->start();
}

void VoskDownloadLanguageJob::generateInstalledLanguageInfo()
{
    auto generateInstalledLanguageJob = new GenerateInstalledLanguageInfoJob(this);
    GenerateInstalledLanguageInfoJob::LanguageInfo info;
    info.pathToStore = VoskEngineUtils::storageLanguagePath() + u'/' + mInfo.name;
    info.info.absoluteLanguageModelPath = VoskEngineUtils::storageLanguagePath() + u'/' + mInfo.name;
    info.info.name = mInfo.name;
    info.info.url = mInfo.url.toString();
    info.info.versionStr = mInfo.version;
    generateInstalledLanguageJob->setInfo(info);

    connect(generateInstalledLanguageJob, &GenerateInstalledLanguageInfoJob::errorText, this, &VoskDownloadLanguageJob::errorText);
    connect(generateInstalledLanguageJob,
            &GenerateInstalledLanguageInfoJob::generatedDone,
            this,
            &VoskDownloadLanguageJob::slotGenerateInstalledLanguageInfoDone);
    generateInstalledLanguageJob->start();
}

void VoskDownloadLanguageJob::slotGenerateInstalledLanguageInfoDone()
{
    Q_EMIT extractDone();
    deleteLater();
}

VoskDownloadLanguageJob::DownloadLanguageInfo VoskDownloadLanguageJob::info() const
{
    return mInfo;
}

void VoskDownloadLanguageJob::setInfo(const DownloadLanguageInfo &newInfo)
{
    mInfo = newInfo;
}

QDebug operator<<(QDebug d, const VoskDownloadLanguageJob::DownloadLanguageInfo &t)
{
    d << "url " << t.url;
    d << "checksum " << t.checksum;
    d << "name " << t.name;
    d << "version " << t.version;
    return d;
}

bool VoskDownloadLanguageJob::DownloadLanguageInfo::isValid() const
{
    return !url.isEmpty() && !name.isEmpty();
}

#include "moc_voskdownloadlanguagejob.cpp"
