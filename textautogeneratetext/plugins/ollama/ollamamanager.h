/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class OllamaManager : public QObject
{
    Q_OBJECT
public:
    explicit OllamaManager(QObject *parent = nullptr);
    ~OllamaManager() override;
};
