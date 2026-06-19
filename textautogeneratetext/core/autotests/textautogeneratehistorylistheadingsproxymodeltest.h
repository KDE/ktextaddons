/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class TextAutoGenerateHistoryListHeadingsProxyModelTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateHistoryListHeadingsProxyModelTest(QObject *parent = nullptr);
    ~TextAutoGenerateHistoryListHeadingsProxyModelTest() override = default;

private Q_SLOTS:
    void shouldHandleNullSourceModel();
    void shouldRejectInvalidIndexes();
};
