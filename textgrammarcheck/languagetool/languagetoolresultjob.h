/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textgrammarcheckprivate_export.h"
#include <QObject>
class QNetworkRequest;
class QNetworkReply;
class QNetworkAccessManager;
namespace TextGrammarCheck
{
class TEXTGRAMMARCHECK_TESTS_EXPORT LanguageToolResultJob : public QObject
{
    Q_OBJECT
public:
    explicit LanguageToolResultJob(QObject *parent = nullptr);
    ~LanguageToolResultJob() override;
    Q_REQUIRED_RESULT bool canStart() const;
    void start();
    Q_REQUIRED_RESULT QStringList arguments() const;
    void setArguments(const QStringList &arguments);

    QNetworkAccessManager *networkAccessManager() const;
    void setNetworkAccessManager(QNetworkAccessManager *networkAccessManager);

    Q_REQUIRED_RESULT QString text() const;
    void setText(const QString &text);

    Q_REQUIRED_RESULT QString url() const;
    void setUrl(const QString &url);

    Q_REQUIRED_RESULT QString language() const;
    void setLanguage(const QString &language);

Q_SIGNALS:
    void finished(const QString &result);
    void error(const QString &errorStr);

private:
    Q_DISABLE_COPY(LanguageToolResultJob)
    enum class JobError {
        NotError,
        EmptyText,
        UrlNotDefined,
        NetworkManagerNotDefined,
        LanguageNotDefined,
    };

    Q_REQUIRED_RESULT LanguageToolResultJob::JobError canStartError() const;
    void slotCheckGrammarFinished();
    void addRequestAttribute(QNetworkRequest &request) const;
    void slotFinish(QNetworkReply *reply);
    QStringList mArguments;
    QString mText;
    QString mUrl;
    QString mLanguage;
    QNetworkAccessManager *mNetworkAccessManager = nullptr;
};
}
