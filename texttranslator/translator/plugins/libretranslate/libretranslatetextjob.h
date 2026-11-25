/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QNetworkReply>
#include <QObject>

class LibreTranslateTextJob : public QObject
{
    Q_OBJECT
public:
    struct LibreTranslateTextInfo {
        QString serverUrl;
        QString apiKey;
        QString inputText;
        QString from;
        QString to;
        bool hasDebug = false;

        [[nodiscard]] bool isValid() const;
    };
    explicit LibreTranslateTextJob(QObject *parent = nullptr);
    ~LibreTranslateTextJob() override;

    [[nodiscard]] bool canStart() const;

    void start();

    [[nodiscard]] LibreTranslateTextInfo info() const;
    void setInfo(const LibreTranslateTextInfo &newInfo);

Q_SIGNALS:
    void translateDone(const QString &result, const QString &jsonDebug);
    void translateFailed(const QString &errorMessage);
    void networkError(QNetworkReply::NetworkError error);

private:
    void parseTranslation(QNetworkReply *reply);
    LibreTranslateTextInfo mInfo;
};
