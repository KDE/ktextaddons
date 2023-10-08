/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "libbergamot_private_export.h"
#include <QCryptographicHash>
#include <QObject>
#include <QUrl>
class QTemporaryFile;
class LIBBERGAMOT_TESTS_EXPORT DownloadLanguageJob : public QObject
{
    Q_OBJECT
public:
    explicit DownloadLanguageJob(QObject *parent = nullptr);
    ~DownloadLanguageJob() override;
    void start();

    Q_REQUIRED_RESULT bool canStart() const;

    Q_REQUIRED_RESULT QUrl url() const;
    void setUrl(const QUrl &newUrl);

    Q_REQUIRED_RESULT QString checkSum() const;
    void setCheckSum(const QString &newCheckSum);

Q_SIGNALS:
    void errorText(const QString &str);
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void extractDone();

private:
    void slotExtractDone();
    void extractLanguage();
    QCryptographicHash *mHash = nullptr;
    QUrl mUrl;
    QString mCheckSum;
    QTemporaryFile *mDestination = nullptr;
};
