/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "managermodeltranslator.h"
#include "bergamotengineutils.h"
#include "extractlanguagejob.h"
#include "libbergamot_debug.h"
#include "translator.h"
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
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        parseListModel(QJsonDocument::fromJson(reply->readAll()).object());
        reply->deleteLater();
    });
    connect(reply, &QNetworkReply::errorOccurred, this, [reply, this](QNetworkReply::NetworkError error) {
        if (error == QNetworkReply::ServiceUnavailableError) {
            Q_EMIT i18n("Error: Engine systems have detected suspicious traffic from your computer network. Please try your request again later.");
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
}

QVector<Translator> ManagerModelTranslator::translators() const
{
    return mTranslators;
}

void ManagerModelTranslator::setTranslators(const QVector<Translator> &newTranslators)
{
    mTranslators = newTranslators;
}

void ManagerModelTranslator::downloadLanguage(const QString &url)
{
    const QUrl u(url);
    QNetworkRequest request(u);
    QNetworkReply *reply = TextTranslator::TranslatorEngineAccessManager::self()->networkManager()->get(request);
    connect(reply, &QNetworkReply::errorOccurred, this, [this, reply, url](QNetworkReply::NetworkError error) {
        if (error == QNetworkReply::ServiceUnavailableError) {
            Q_EMIT i18n("Error: Engine systems have detected suspicious traffic from your computer network. Please try your request again later.");
        } else {
            Q_EMIT errorText(i18n("Impossible to access to url: %1", url));
        }
        reply->deleteLater();
    });

    connect(reply, &QNetworkReply::downloadProgress, this, &ManagerModelTranslator::slotProgress);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        reply->deleteLater();
        // parseTranslation(reply);
    });
    connect(reply, &QIODevice::readyRead, this, [=] {
        QByteArray buffer = reply->readAll();
        // TODO
    });
}

void ManagerModelTranslator::slotProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    // TODO
}

void ManagerModelTranslator::extractLanguage()
{
    auto extraJob = new ExtractLanguageJob(this);
    // TODO add source/target
    connect(extraJob, &ExtractLanguageJob::errorText, this, &ManagerModelTranslator::errorText);
    connect(extraJob, &ExtractLanguageJob::finished, this, &ManagerModelTranslator::slotExtractDone);

    extraJob->start();
}

void ManagerModelTranslator::slotExtractDone()
{
    // TODO
}

#include "moc_managermodeltranslator.cpp"
