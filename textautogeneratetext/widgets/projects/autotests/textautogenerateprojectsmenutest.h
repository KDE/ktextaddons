/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateProjectsMenuTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateProjectsMenuTest(QObject *parent = nullptr);
    ~TextAutoGenerateProjectsMenuTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldShowOnlyManageActionWithoutChatId();
};
