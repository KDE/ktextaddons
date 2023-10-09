/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "managermodelvoskspeechtotext.h"
#include "downloadlanguagejob.h"
#include "libvoskspeechtotext_debug.h"
#include "speechtotext/speechtotextengineaccessmanager.h"
#include "voskengineutils.h"
#include <KLocalizedString>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>

ManagerModelVoskSpeechToText::ManagerModelVoskSpeechToText(QObject *parent)
    : QObject{parent}
{
}

ManagerModelVoskSpeechToText::~ManagerModelVoskSpeechToText() = default;

ManagerModelVoskSpeechToText *ManagerModelVoskSpeechToText::self()
{
    static ManagerModelVoskSpeechToText s_self;
    return &s_self;
}

void ManagerModelVoskSpeechToText::downloadListModels()
{
    const QUrl url = QUrl(VoskEngineUtils::defaultVoskRepository());
    // qDebug() << " url " << url;
    QNetworkReply *reply = TextSpeechToText::SpeechToTextEngineAccessManager::self()->networkManager()->get(QNetworkRequest(url));

    connect(reply, &QNetworkReply::sslErrors, this, [](const QList<QSslError> &errors) {
        qDebug() << "Ssl Error: " << errors;
    });
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        const auto readAll = reply->readAll();
        // qDebug() << " readAll " << readAll;
        parseListModel(QJsonDocument::fromJson(readAll).object());
        reply->deleteLater();
    });
    connect(reply, &QNetworkReply::errorOccurred, this, [this](QNetworkReply::NetworkError error) {
        if (error == QNetworkReply::ServiceUnavailableError) {
            Q_EMIT errorText(i18n("Error: Engine systems have detected suspicious traffic from your computer network. Please try your request again later."));
        } else {
            Q_EMIT errorText(i18n("Impossible to access to url: %1", VoskEngineUtils::defaultVoskRepository()));
        }
    });
}

void ManagerModelVoskSpeechToText::loadModelList(const QString &fileName)
{
    QFile f(fileName);
    if (f.open(QIODevice::ReadOnly)) {
        const QByteArray content = f.readAll();
        f.close();
        const QJsonDocument doc = QJsonDocument::fromJson(content);
        const QJsonObject fields = doc.object();
        parseListModel(fields);
    } else {
        qCWarning(LIBVOSKSPEECHTOTEXT_LOG) << "Impossible to open " << fileName;
    }
}

void ManagerModelVoskSpeechToText::parseListModel(const QJsonObject &obj)
{
    mSpeechToTextInfos.clear();
    const QJsonArray arrays = obj[QLatin1String("models")].toArray();
    for (const QJsonValue &current : arrays) {
        if (current.type() == QJsonValue::Object) {
            VoskSpeechToTextInfo speechTextInfo;
            const QJsonObject translatorObject = current.toObject();
            speechTextInfo.parse(translatorObject);
            if (speechTextInfo.isValid()) {
                mSpeechToTextInfos.append(std::move(speechTextInfo));
            }
        } else {
            qCWarning(LIBVOSKSPEECHTOTEXT_LOG) << " Problem during parsing" << current;
        }
    }
    qCDebug(LIBVOSKSPEECHTOTEXT_LOG) << " mTranslators " << mSpeechToTextInfos.count();
    Q_EMIT downLoadModelListDone();
}

QVector<VoskSpeechToTextInfo> ManagerModelVoskSpeechToText::translators() const
{
    return mSpeechToTextInfos;
}

void ManagerModelVoskSpeechToText::setTranslators(const QVector<VoskSpeechToTextInfo> &newTranslators)
{
    mSpeechToTextInfos = newTranslators;
}

void ManagerModelVoskSpeechToText::downloadLanguage(const QString &url, const QString &checkSum)
{
    auto downloadJob = new DownloadLanguageJob(this);
    downloadJob->setUrl(QUrl(url));
    downloadJob->setCheckSum(checkSum);
    const QString name = url;
    connect(downloadJob, &DownloadLanguageJob::errorText, this, &ManagerModelVoskSpeechToText::errorText);
    connect(downloadJob, &DownloadLanguageJob::extractDone, this, &ManagerModelVoskSpeechToText::extractDone);
    connect(downloadJob, &DownloadLanguageJob::downloadProgress, this, [this, url](qint64 bytesReceived, qint64 bytesTotal) {
        ManagerModelVoskSpeechToText::ProgressInfo info;
        info.bytesReceived = bytesReceived;
        info.bytesTotal = bytesTotal;
        info.languageName = url;
        Q_EMIT progress(std::move(info));
    });
    downloadJob->start();
}

bool ManagerModelVoskSpeechToText::needDownloadModelList() const
{
    return mSpeechToTextInfos.isEmpty();
}

#include "moc_managermodelvoskspeechtotext.cpp"
