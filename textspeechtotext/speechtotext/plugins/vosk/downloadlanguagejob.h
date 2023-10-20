/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "libvoskspeechtotext_private_export.h"
#include <QCryptographicHash>
#include <QObject>
#include <QUrl>
class QTemporaryFile;
class LIBVOSKSPEECHTOTEXT_TESTS_EXPORT DownloadLanguageJob : public QObject
{
    Q_OBJECT
public:
    struct LIBVOSKSPEECHTOTEXT_TESTS_EXPORT DownloadLanguageInfo {
        QUrl url;
        QString checksum;
        QString name;
        QString version;
        Q_REQUIRED_RESULT bool isValid() const;
    };
    explicit DownloadLanguageJob(QObject *parent = nullptr);
    ~DownloadLanguageJob() override;
    void start();

    Q_REQUIRED_RESULT bool canStart() const;

    Q_REQUIRED_RESULT DownloadLanguageInfo info() const;
    void setInfo(const DownloadLanguageInfo &newInfo);

Q_SIGNALS:
    void errorText(const QString &str);
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void extractDone();

private:
    void generateInstalledLanguageInfo();
    void extractLanguage();
    void slotGenerateInstalledLanguageInfoDone();
    DownloadLanguageInfo mInfo;
    QCryptographicHash *mHash = nullptr;
    QTemporaryFile *mDestination = nullptr;
};
Q_DECLARE_TYPEINFO(DownloadLanguageJob::DownloadLanguageInfo, Q_MOVABLE_TYPE);
LIBVOSKSPEECHTOTEXT_EXPORT QDebug operator<<(QDebug d, const DownloadLanguageJob::DownloadLanguageInfo &t);