/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "libvoskspeechtotext_private_export.h"
#include <QCryptographicHash>
#include <QObject>
#include <QUrl>
class QTemporaryFile;
class LIBVOSKSPEECHTOTEXT_TESTS_EXPORT VoskDownloadLanguageJob : public QObject
{
    Q_OBJECT
public:
    struct LIBVOSKSPEECHTOTEXT_TESTS_EXPORT DownloadLanguageInfo {
        QUrl url;
        QString checksum;
        QString name;
        QString version;
        [[nodiscard]] bool isValid() const;
    };
    explicit VoskDownloadLanguageJob(QObject *parent = nullptr);
    ~VoskDownloadLanguageJob() override;
    void start();

    [[nodiscard]] bool canStart() const;

    [[nodiscard]] DownloadLanguageInfo info() const;
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
Q_DECLARE_TYPEINFO(VoskDownloadLanguageJob::DownloadLanguageInfo, Q_MOVABLE_TYPE);
LIBVOSKSPEECHTOTEXT_EXPORT QDebug operator<<(QDebug d, const VoskDownloadLanguageJob::DownloadLanguageInfo &t);
