/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateManageProjectsWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateManageProjectsWidgetTest(QObject *parent = nullptr);
    ~TextAutoGenerateManageProjectsWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldStoreProjects();
    void shouldEnableButtonsWhenSelectingProject();
};
