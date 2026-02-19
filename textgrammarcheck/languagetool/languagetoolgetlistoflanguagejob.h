/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

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
/*!
 * \class TextGrammarCheck::LanguageToolGetListOfLanguageJob
 * \inheaderfile TextGrammarCheck/LanguageToolGetListOfLanguageJob
 * \inmodule TextGrammarCheck
 * \brief Fetches list of available languages from LanguageTool service.
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTGRAMMARCHECK_EXPORT LanguageToolGetListOfLanguageJob : public QObject
{
    Q_OBJECT
public:
    /*! Constructs a new LanguageToolGetListOfLanguageJob. */
    explicit LanguageToolGetListOfLanguageJob(QObject *parent = nullptr);
    /*! Destroys the job. */
    ~LanguageToolGetListOfLanguageJob() override;

    /*! Returns whether the job can be started. */
    [[nodiscard]] bool canStart() const;
    /*! Starts fetching the list of available languages. */
    void start();

    /*! Returns the path to the languages list endpoint. */
    [[nodiscard]] QString listOfLanguagePath() const;
    /*! Sets the path to the languages list endpoint. */
    void setListOfLanguagePath(const QString &listOfLanguagePath);

    /*! Returns the network access manager used for requests. */
    QNetworkAccessManager *networkAccessManager() const;
    /*! Sets the network access manager to use for requests. */
    void setNetworkAccessManager(QNetworkAccessManager *networkAccessManager);

    /*! Returns the base URL for the LanguageTool server. */
    [[nodiscard]] QString url() const;
    /*! Sets the base URL for the LanguageTool server. */
    void setUrl(const QString &url);

Q_SIGNALS:
    /*! Emitted when the language list has been successfully fetched. */
    void finished(const QString &result);
    /*! Emitted when an error occurs while fetching the language list. */
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
