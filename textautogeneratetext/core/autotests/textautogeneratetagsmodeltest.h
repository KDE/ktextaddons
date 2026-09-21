/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateTagsModelTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTagsModelTest(QObject *parent = nullptr);
    ~TextAutoGenerateTagsModelTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldAddTag();
    void shouldRemoveTag();
    void shouldUpdateTag();
    void shouldClearTags();
};
