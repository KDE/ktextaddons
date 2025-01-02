/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "libbergamot_export.h"
#include "translator.h"
#include <QObject>

class LIBBERGAMOT_EXPORT ManagerModelTranslator : public QObject
{
    Q_OBJECT
public:
    struct ProgressInfo {
        QString languageName;
        qint64 bytesReceived = -1;
        qint64 bytesTotal = -1;
    };
    explicit ManagerModelTranslator(QObject *parent = nullptr);
    ~ManagerModelTranslator() override;

    static ManagerModelTranslator *self();

    void downloadListModels();

    [[nodiscard]] QVector<Translator> translators() const;
    void setTranslators(const QVector<Translator> &newTranslators);

    void loadModelList(const QString &fileName);

    void downloadLanguage(const QString &url, const QString &checkSum);
    [[nodiscard]] bool needDownloadModelList() const;
Q_SIGNALS:
    void errorText(const QString &str);
    void progress(const ManagerModelTranslator::ProgressInfo &info);
    void extractDone();
    void downLoadModelListDone();

private:
    LIBBERGAMOT_NO_EXPORT void parseListModel(const QJsonObject &obj);
    QVector<Translator> mTranslators;
};
Q_DECLARE_TYPEINFO(ManagerModelTranslator::ProgressInfo, Q_MOVABLE_TYPE);
