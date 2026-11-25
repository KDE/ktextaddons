/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include <QNetworkReply>
#include <QObject>

class LibreTranslateLanguagesJob : public QObject
{
    Q_OBJECT
public:
    struct LibreTranslateLanguagesInfo {
        QString apiKey;
        QString serverUrl;

        [[nodiscard]] bool isValid() const;
    };
    explicit LibreTranslateLanguagesJob(QObject *parent = nullptr);
    ~LibreTranslateLanguagesJob() override;

    [[nodiscard]] bool canStart() const;

    void start();

    [[nodiscard]] LibreTranslateLanguagesInfo info() const;
    void setInfo(const LibreTranslateLanguagesInfo &newInfo);

Q_SIGNALS:
    void getLanguagesFailed();
    void getLanguagesDone();
    void networkError(QNetworkReply::NetworkError error);

private:
    LibreTranslateLanguagesInfo mInfo;
};
