/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include <QMap>
#include <QNetworkReply>
#include <QObject>
#include <QStringList>

class LibreTranslateLanguagesJob : public QObject
{
    Q_OBJECT
public:
    struct LibreTranslateLanguagesInfo {
        QString serverUrl;

        [[nodiscard]] bool isValid() const;
    };
    explicit LibreTranslateLanguagesJob(QObject *parent = nullptr);
    ~LibreTranslateLanguagesJob() override;

    [[nodiscard]] bool canStart() const;

    void start();

    [[nodiscard]] LibreTranslateLanguagesInfo info() const;
    void setInfo(const LibreTranslateLanguagesInfo &newInfo);

    // Lang -> supported language (to)
    [[nodiscard]] static QMap<QString, QStringList> parseLanguages(const QByteArray &data);

Q_SIGNALS:
    void getLanguagesFailed(const QString &errorStr);
    void getLanguagesDone(const QMap<QString, QStringList> &languages);
    void networkError(QNetworkReply::NetworkError error);

private:
    void parseReply(QNetworkReply *reply);
    LibreTranslateLanguagesInfo mInfo;
};
