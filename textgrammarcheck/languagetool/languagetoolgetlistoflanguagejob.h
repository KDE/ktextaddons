/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textgrammarcheck_export.h"
#include <QNetworkRequest>
#include <QObject>
class QNetworkAccessManager;
class QNetworkReply;
namespace TextGrammarCheck
{
class TEXTGRAMMARCHECK_EXPORT LanguageToolGetListOfLanguageJob : public QObject
{
    Q_OBJECT
public:
    explicit LanguageToolGetListOfLanguageJob(QObject *parent = nullptr);
    ~LanguageToolGetListOfLanguageJob() override;

    [[nodiscard]] bool canStart() const;
    void start();

    [[nodiscard]] QString listOfLanguagePath() const;
    void setListOfLanguagePath(const QString &listOfLanguagePath);

    QNetworkAccessManager *networkAccessManager() const;
    void setNetworkAccessManager(QNetworkAccessManager *networkAccessManager);

    [[nodiscard]] QString url() const;
    void setUrl(const QString &url);

Q_SIGNALS:
    void finished(const QString &result);
    void error(const QString &errorStr);

private:
    Q_DISABLE_COPY(LanguageToolGetListOfLanguageJob)
    TEXTGRAMMARCHECK_NO_EXPORT void addRequestAttribute(QNetworkRequest &request) const;
    TEXTGRAMMARCHECK_NO_EXPORT void slotCheckListOfLanguagesFinished();
    TEXTGRAMMARCHECK_NO_EXPORT void slotFinish(QNetworkReply *reply);

    QString mListOfLanguagePath;
    QNetworkAccessManager *mNetworkAccessManager = nullptr;
    QString mUrl;
};
}
