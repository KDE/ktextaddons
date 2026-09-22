/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateManageTagsDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateManageTagsDialogTest(QObject *parent = nullptr);
    ~TextAutoGenerateManageTagsDialogTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldStoreTags();
};
