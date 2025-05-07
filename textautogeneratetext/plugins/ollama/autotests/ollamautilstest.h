/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class OllamaUtilsTest : public QObject
{
    Q_OBJECT
public:
    explicit OllamaUtilsTest(QObject *parent = nullptr);
    ~OllamaUtilsTest() override;
private Q_SLOTS:
    void shouldHaveUtilsPath();
};
