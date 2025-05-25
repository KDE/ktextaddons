/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class OllamaModelDownloadProgressWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit OllamaModelDownloadProgressWidgetTest(QObject *parent = nullptr);
    ~OllamaModelDownloadProgressWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
