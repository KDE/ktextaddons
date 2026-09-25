/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class TextAutoGenerateHistorySortFilterProxyModelTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateHistorySortFilterProxyModelTest(QObject *parent = nullptr);
    ~TextAutoGenerateHistorySortFilterProxyModelTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldFilterByTags();
    void shouldDropChatOnProjectThroughTheWholeChain();
};
