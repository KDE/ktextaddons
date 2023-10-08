/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "libbergamot_private_export.h"
#include <QObject>

class LIBBERGAMOT_TESTS_EXPORT ExtractLanguageJob : public QObject
{
    Q_OBJECT
public:
    explicit ExtractLanguageJob(QObject *parent = nullptr);
    ~ExtractLanguageJob() override;

    Q_REQUIRED_RESULT bool canStart() const;
    void start();

    Q_REQUIRED_RESULT QString source() const;
    void setSource(const QString &newSource);

Q_SIGNALS:
    void finished();
    void errorText(const QString &str);

private:
    QString mSource;
};
