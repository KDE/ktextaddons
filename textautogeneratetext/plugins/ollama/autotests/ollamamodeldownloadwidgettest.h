/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class OllamaModelDownloadWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit OllamaModelDownloadWidgetTest(QObject *parent = nullptr);
    ~OllamaModelDownloadWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldVerifyName();
    void shouldEmitDownloadModel();
};
