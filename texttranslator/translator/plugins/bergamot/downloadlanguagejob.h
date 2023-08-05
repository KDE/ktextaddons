/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "libbergamot_private_export.h"
#include <QObject>

class LIBBERGAMOT_TESTS_EXPORT DownloadLanguageJob : public QObject
{
    Q_OBJECT
public:
    explicit DownloadLanguageJob(QObject *parent = nullptr);
    ~DownloadLanguageJob() override;
    void start();
    Q_REQUIRED_RESULT bool canStart() const;
};
