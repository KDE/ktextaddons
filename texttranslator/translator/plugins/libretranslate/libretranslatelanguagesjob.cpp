/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "libretranslatelanguagesjob.h"
#include "libretranslatetranslator_debug.h"
#include <KLocalizedString>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <TextTranslator/TranslatorEngineAccessManager>

using namespace Qt::Literals::StringLiterals;
LibreTranslateLanguagesJob::LibreTranslateLanguagesJob(QObject *parent)
    : QObject{parent}
{
}

LibreTranslateLanguagesJob::~LibreTranslateLanguagesJob() = default;

bool LibreTranslateLanguagesJob::canStart() const
{
    return mInfo.isValid();
}

void LibreTranslateLanguagesJob::start()
{
    if (!canStart()) {
        qCWarning(TRANSLATOR_LIBRETRANSLATE_LOG) << "Impossible to start LibreTranslateLanguagesJob";
        Q_EMIT getLanguagesFailed(i18n("Server url is not defined."));
        deleteLater();
        return;
    }
    const auto url = QUrl(u"%1/languages"_s.arg(mInfo.serverUrl));
    QNetworkRequest request;
    request.setUrl(url);

    qCDebug(TRANSLATOR_LIBRETRANSLATE_LOG) << " url " << url;

    QNetworkReply *reply = TextTranslator::TranslatorEngineAccessManager::self()->networkManager()->get(request);
    connect(reply, &QNetworkReply::errorOccurred, this, [this](QNetworkReply::NetworkError error) {
        Q_EMIT networkError(error);
    });
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        reply->deleteLater();
        parseReply(reply);
        deleteLater();
    });
}

LibreTranslateLanguagesJob::LibreTranslateLanguagesInfo LibreTranslateLanguagesJob::info() const
{
    return mInfo;
}

void LibreTranslateLanguagesJob::setInfo(const LibreTranslateLanguagesInfo &newInfo)
{
    mInfo = newInfo;
}

bool LibreTranslateLanguagesJob::LibreTranslateLanguagesInfo::isValid() const
{
    return !serverUrl.isEmpty();
}

void LibreTranslateLanguagesJob::parseReply(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        Q_EMIT getLanguagesFailed(reply->errorString());
        return;
    }
    const QMap<QString, QStringList> languages = parseLanguages(reply->readAll());
    if (languages.isEmpty()) {
        Q_EMIT getLanguagesFailed(i18n("Server returned an invalid languages list."));
        return;
    }
    Q_EMIT getLanguagesDone(languages);
}

QMap<QString, QStringList> LibreTranslateLanguagesJob::parseLanguages(const QByteArray &data)
{
    QMap<QString, QStringList> languages;
    const QJsonArray array = QJsonDocument::fromJson(data).array();
    for (const auto &value : array) {
        const QJsonObject obj = value.toObject();
        const QString code = obj.value("code"_L1).toString();
        if (code.isEmpty()) {
            continue;
        }
        QStringList targets;
        const QJsonArray targetsArray = obj.value("targets"_L1).toArray();
        for (const auto &targetValue : targetsArray) {
            // A language is listed as its own target: skip it
            if (const QString target = targetValue.toString(); !target.isEmpty() && target != code) {
                targets.append(target);
            }
        }
        languages.insert(code, targets);
    }
    return languages;
}

#include "moc_libretranslatelanguagesjob.cpp"
