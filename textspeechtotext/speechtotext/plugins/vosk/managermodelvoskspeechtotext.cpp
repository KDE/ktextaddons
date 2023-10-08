/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "managermodelvoskspeechtotext.h"
#include "bergamotengineutils.h"
#include "downloadlanguagejob.h"
#include "libbergamot_debug.h"
#include <KLocalizedString>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <TextTranslator/TranslatorEngineAccessManager>

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
    const QUrl url = QUrl(BergamotEngineUtils::defaultBergamotRepository());
    // qDebug() << " url " << url;
    QNetworkReply *reply = TextTranslator::TranslatorEngineAccessManager::self()->networkManager()->get(QNetworkRequest(url));

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
            Q_EMIT errorText(i18n("Impossible to access to url: %1", BergamotEngineUtils::defaultBergamotRepository()));
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
        qCWarning(TRANSLATOR_LIBBERGAMOT_LOG) << "Impossible to open " << fileName;
    }
}

void ManagerModelVoskSpeechToText::parseListModel(const QJsonObject &obj)
{
    mTranslators.clear();
    const QJsonArray arrays = obj[QLatin1String("models")].toArray();
    for (const QJsonValue &current : arrays) {
        if (current.type() == QJsonValue::Object) {
            Translator translator;
            const QJsonObject translatorObject = current.toObject();
            translator.parse(translatorObject);
            if (translator.isValid()) {
                mTranslators.append(std::move(translator));
            }
        } else {
            qCWarning(TRANSLATOR_LIBBERGAMOT_LOG) << " Problem during parsing" << current;
        }
    }
    qCDebug(TRANSLATOR_LIBBERGAMOT_LOG) << " mTranslators " << mTranslators.count();
    Q_EMIT downLoadModelListDone();
}

QVector<Translator> ManagerModelVoskSpeechToText::translators() const
{
    return mTranslators;
}

void ManagerModelVoskSpeechToText::setTranslators(const QVector<Translator> &newTranslators)
{
    mTranslators = newTranslators;
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
    return mTranslators.isEmpty();
}

#include "moc_managermodeltranslator.cpp"
