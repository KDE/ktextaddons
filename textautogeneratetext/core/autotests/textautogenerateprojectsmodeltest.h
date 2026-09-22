/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateProjectsModelTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateProjectsModelTest(QObject *parent = nullptr);
    ~TextAutoGenerateProjectsModelTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldAddProject();
    void shouldRemoveProject();
    void shouldUpdateProject();
    void shouldClearProjects();
    void shouldReturnNameAndColor();
};
