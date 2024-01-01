/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class VoskEngineUtilsTest : public QObject
{
    Q_OBJECT
public:
    explicit VoskEngineUtilsTest(QObject *parent = nullptr);
    ~VoskEngineUtilsTest() override = default;
private Q_SLOTS:
    void shouldDefineStoragePath();
    void shouldDefineRepositoryPath();
    void shouldVerifyLanguageInstalledStruct();
    void shouldSaveLoadLanguageInstalled();
};
