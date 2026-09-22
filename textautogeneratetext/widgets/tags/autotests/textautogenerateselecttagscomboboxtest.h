/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class TextAutoGenerateSelectTagsComboBoxTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSelectTagsComboBoxTest(QObject *parent = nullptr);
    ~TextAutoGenerateSelectTagsComboBoxTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldFillTags();
    void shouldSelectTags();
    void shouldClearSelectionWhenSettingTags();
};
