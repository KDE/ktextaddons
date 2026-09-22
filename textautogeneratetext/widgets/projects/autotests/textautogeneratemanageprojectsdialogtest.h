/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateManageProjectsDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateManageProjectsDialogTest(QObject *parent = nullptr);
    ~TextAutoGenerateManageProjectsDialogTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldStoreProjects();
};
