/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolgetlistoflanguagejob.h"
using namespace Qt::Literals::StringLiterals;

#include "textgrammarcheck_debug.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
using namespace TextGrammarCheck;
LanguageToolGetListOfLanguageJob::LanguageToolGetListOfLanguageJob(QObject *parent)
    : QObject(parent)
{
}

LanguageToolGetListOfLanguageJob::~LanguageToolGetListOfLanguageJob() = default;

bool LanguageToolGetListOfLanguageJob::canStart() const
{
    if (!mNetworkAccessManager || mUrl.isEmpty()) {
        return false;
    }
    return true;
}

void LanguageToolGetListOfLanguageJob::start()
{
    if (!canStart()) {
        qCWarning(TEXTGRAMMARCHECK_LOG) << "Impossible to start LanguageToolGetListOfLanguageJob";
        deleteLater();
        return;
    }
    QNetworkRequest request(QUrl::fromUserInput(mUrl));
    addRequestAttribute(request);
    QNetworkReply *reply = mNetworkAccessManager->get(request);
    connect(reply, &QNetworkReply::finished, this, &LanguageToolGetListOfLanguageJob::slotCheckListOfLanguagesFinished);
    connect(mNetworkAccessManager, &QNetworkAccessManager::finished, this, &LanguageToolGetListOfLanguageJob::slotFinish);
}

void LanguageToolGetListOfLanguageJob::slotFinish(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qCWarning(TEXTGRAMMARCHECK_LOG) << " Error reply - " << reply->errorString();
        Q_EMIT error(reply->errorString());
    }
}

void LanguageToolGetListOfLanguageJob::slotCheckListOfLanguagesFinished()
{
    auto reply = qobject_cast<QNetworkReply *>(sender());
    if (reply) {
        const QByteArray data = reply->readAll();
        Q_EMIT finished(QString::fromUtf8(data));
        reply->deleteLater();
    }
    deleteLater();
}

void LanguageToolGetListOfLanguageJob::addRequestAttribute(QNetworkRequest &request) const
{
    request.setHeader(QNetworkRequest::ContentTypeHeader, u"application/x-www-form-urlencoded"_s);
}

QString LanguageToolGetListOfLanguageJob::listOfLanguagePath() const
{
    return mListOfLanguagePath;
}

void LanguageToolGetListOfLanguageJob::setListOfLanguagePath(const QString &getListOfLanguagePath)
{
    mListOfLanguagePath = getListOfLanguagePath;
}

QNetworkAccessManager *LanguageToolGetListOfLanguageJob::networkAccessManager() const
{
    return mNetworkAccessManager;
}

void LanguageToolGetListOfLanguageJob::setNetworkAccessManager(QNetworkAccessManager *networkAccessManager)
{
    mNetworkAccessManager = networkAccessManager;
}

QString LanguageToolGetListOfLanguageJob::url() const
{
    return mUrl;
}

void LanguageToolGetListOfLanguageJob::setUrl(const QString &url)
{
    mUrl = url;
}

#include "moc_languagetoolgetlistoflanguagejob.cpp"
