/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateManageTagsWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateManageTagsWidgetTest(QObject *parent = nullptr);
    ~TextAutoGenerateManageTagsWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldStoreTags();
    void shouldEnableButtonsWhenSelectingTag();
};
