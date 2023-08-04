/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "managermodeltranslator.h"
#include "bergamotengineutils.h"
#include "libbergamot_debug.h"
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

#include "moc_managermodeltranslator.cpp"
