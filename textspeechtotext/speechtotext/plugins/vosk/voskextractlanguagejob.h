/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "libvoskspeechtotext_private_export.h"
#include <QObject>
class KArchiveDirectory;
class LIBVOSKSPEECHTOTEXT_TESTS_EXPORT VoskExtractLanguageJob : public QObject
{
    Q_OBJECT
public:
    explicit VoskExtractLanguageJob(QObject *parent = nullptr);
    ~VoskExtractLanguageJob() override;

    Q_REQUIRED_RESULT bool canStart() const;
    void start();

    Q_REQUIRED_RESULT QString source() const;
    void setSource(const QString &newSource);

Q_SIGNALS:
    void finished();
    void errorText(const QString &str);

private:
    QString mSource;
    void extractRecursive(const KArchiveDirectory *dir, const QString &path);
};
