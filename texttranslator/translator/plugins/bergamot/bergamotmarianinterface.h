/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "libbergamot_export.h"
#include <QObject>

class LIBBERGAMOT_EXPORT BergamotMarianInterface : public QObject
{
    Q_OBJECT
public:
    explicit BergamotMarianInterface(QObject *parent = nullptr);
    ~BergamotMarianInterface() override;

    void translate(const QString &str);
};
