/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "managermodeltranslator.h"
#include "bergamottranslator_debug.h"
#include "bergamotutils.h"
#include "translator.h"
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

void ManagerModelTranslator::downloadListModels()
{
    QNetworkReply *reply =
        TextTranslator::TranslatorEngineAccessManager::self()->networkManager()->get(QNetworkRequest(QUrl(BergamotUtils::defaultBergamotRepository())));
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        parseListModel(QJsonDocument::fromJson(reply->readAll()).object());
    });
    connect(reply, &QNetworkReply::errorOccurred, this, [this, reply](QNetworkReply::NetworkError error) {
        // TODO slotError(error);
        reply->deleteLater();
    });
}

void ManagerModelTranslator::parseListModel(const QJsonObject &obj)
{
    const QJsonArray arrays = obj[QStringLiteral("models")].toArray();
    for (const QJsonValue &current : arrays) {
        if (current.type() == QJsonValue::Object) {
            Translator translator;
            const QJsonObject translatorObject = current.toObject();
            translator.parse(translatorObject);
            // TODO
        } else {
            qCWarning(TRANSLATOR_BERGAMOT_LOG) << " Problem during parsing";
        }
    }
}

#include "moc_managermodeltranslator.cpp"
