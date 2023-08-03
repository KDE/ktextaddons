/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class ManagerModelTranslator : public QObject
{
    Q_OBJECT
public:
    explicit ManagerModelTranslator(QObject *parent = nullptr);
    ~ManagerModelTranslator() override;
};
