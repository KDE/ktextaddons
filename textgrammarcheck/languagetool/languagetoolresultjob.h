/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

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
    [[nodiscard]] bool canStart() const;
    void start();
    [[nodiscard]] QStringList arguments() const;
    void setArguments(const QStringList &arguments);

    QNetworkAccessManager *networkAccessManager() const;
    void setNetworkAccessManager(QNetworkAccessManager *networkAccessManager);

    [[nodiscard]] QString text() const;
    void setText(const QString &text);

    [[nodiscard]] QString url() const;
    void setUrl(const QString &url);

    [[nodiscard]] QString language() const;
    void setLanguage(const QString &language);

Q_SIGNALS:
    void finished(const QString &result);
    void error(const QString &errorStr);

private:
    Q_DISABLE_COPY(LanguageToolResultJob)
    enum class JobError : uint8_t {
        NotError,
        EmptyText,
        UrlNotDefined,
        NetworkManagerNotDefined,
        LanguageNotDefined,
    };

    [[nodiscard]] LanguageToolResultJob::JobError canStartError() const;
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
