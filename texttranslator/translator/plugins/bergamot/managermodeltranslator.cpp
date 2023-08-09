/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "managermodeltranslator.h"
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

ManagerModelTranslator::ManagerModelTranslator(QObject *parent)
    : QObject{parent}
{
}

ManagerModelTranslator::~ManagerModelTranslator() = default;

ManagerModelTranslator *ManagerModelTranslator::self()
{
    static ManagerModelTranslator s_self;
    return &s_self;
}

void ManagerModelTranslator::downloadListModels()
{
    QNetworkReply *reply =
        TextTranslator::TranslatorEngineAccessManager::self()->networkManager()->get(QNetworkRequest(QUrl(BergamotEngineUtils::defaultBergamotRepository())));

    connect(reply, &QNetworkReply::sslErrors, this, [](const QList<QSslError> &errors) {
        qDebug() << "Ssl Error: " << errors;
    });
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        const auto readAll = reply->readAll();
        parseListModel(QJsonDocument::fromJson(readAll).object());
        reply->deleteLater();
    });
    connect(reply, &QNetworkReply::errorOccurred, this, [reply, this](QNetworkReply::NetworkError error) {
        if (error == QNetworkReply::ServiceUnavailableError) {
            Q_EMIT errorText(i18n("Error: Engine systems have detected suspicious traffic from your computer network. Please try your request again later."));
        } else {
            Q_EMIT errorText(i18n("Impossible to access to url: %1", BergamotEngineUtils::defaultBergamotRepository()));
        }
        reply->deleteLater();
    });
}

void ManagerModelTranslator::loadModelList(const QString &fileName)
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

void ManagerModelTranslator::parseListModel(const QJsonObject &obj)
{
    mTranslators.clear();
    const QJsonArray arrays = obj[QStringLiteral("models")].toArray();
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
    qCWarning(TRANSLATOR_LIBBERGAMOT_LOG) << " mTranslators " << mTranslators.count();
    Q_EMIT downLoadModelListDone();
}

QVector<Translator> ManagerModelTranslator::translators() const
{
    return mTranslators;
}

void ManagerModelTranslator::setTranslators(const QVector<Translator> &newTranslators)
{
    mTranslators = newTranslators;
}

void ManagerModelTranslator::downloadLanguage(const QString &url, const QString &checkSum)
{
    auto downloadJob = new DownloadLanguageJob(this);
    downloadJob->setUrl(QUrl(url));
    downloadJob->setCheckSum(checkSum);
    const QString name = url;
    connect(downloadJob, &DownloadLanguageJob::errorText, this, &ManagerModelTranslator::errorText);
    connect(downloadJob, &DownloadLanguageJob::extractDone, this, &ManagerModelTranslator::extractDone);
    connect(downloadJob, &DownloadLanguageJob::downloadProgress, this, [this, url](qint64 bytesReceived, qint64 bytesTotal) {
        ManagerModelTranslator::ProgressInfo info;
        info.bytesReceived = bytesReceived;
        info.bytesTotal = bytesTotal;
        info.languageName = url;
        Q_EMIT progress(std::move(info));
    });
    downloadJob->start();
}

bool ManagerModelTranslator::needDownloadModelList() const
{
    return mTranslators.isEmpty();
}

#include "moc_managermodeltranslator.cpp"
