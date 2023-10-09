/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "libvoskspeechtotext_export.h"
#include "voskspeechtotextinfo.h"
#include <QObject>

class LIBVOSKSPEECHTOTEXT_EXPORT ManagerModelVoskSpeechToText : public QObject
{
    Q_OBJECT
public:
    struct ProgressInfo {
        QString languageName;
        qint64 bytesReceived = -1;
        qint64 bytesTotal = -1;
    };
    explicit ManagerModelVoskSpeechToText(QObject *parent = nullptr);
    ~ManagerModelVoskSpeechToText() override;

    static ManagerModelVoskSpeechToText *self();

    void downloadListModels();

    Q_REQUIRED_RESULT QVector<VoskSpeechToTextInfo> speechToTextInfos() const;
    void setSpeechToTextInfos(const QVector<VoskSpeechToTextInfo> &newTranslators);

    void loadModelList(const QString &fileName);

    void downloadLanguage(const QString &url, const QString &checkSum);
    Q_REQUIRED_RESULT bool needDownloadModelList() const;
Q_SIGNALS:
    void errorText(const QString &str);
    void progress(const ManagerModelVoskSpeechToText::ProgressInfo &info);
    void extractDone();
    void downLoadModelListDone();

private:
    LIBVOSKSPEECHTOTEXT_NO_EXPORT void parseListModel(const QJsonObject &obj);
    QVector<VoskSpeechToTextInfo> mSpeechToTextInfos;
};
Q_DECLARE_TYPEINFO(ManagerModelVoskSpeechToText::ProgressInfo, Q_MOVABLE_TYPE);
