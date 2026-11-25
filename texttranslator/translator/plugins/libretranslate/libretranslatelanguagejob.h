/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class LibreTranslateLanguageJob : public QObject
{
    Q_OBJECT
public:
    struct LibreTranslateLanguageInfo {
        QString apiKey;
        QString serverUrl;

        [[nodiscard]] bool isValid() const;
    };
    explicit LibreTranslateLanguageJob(QObject *parent = nullptr);
    ~LibreTranslateLanguageJob() override;

    [[nodiscard]] bool canStart() const;

    void start();

    [[nodiscard]] LibreTranslateLanguageInfo info() const;
    void setInfo(const LibreTranslateLanguageInfo &newInfo);

Q_SIGNALS:
    void getLanguagesFailed();
    void getLanguagesDone();

private:
    LibreTranslateLanguageInfo mInfo;
};
