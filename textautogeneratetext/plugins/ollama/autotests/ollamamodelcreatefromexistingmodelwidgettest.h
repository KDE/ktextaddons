/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class OllamaModelCreateFromExistingModelWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit OllamaModelCreateFromExistingModelWidgetTest(QObject *parent = nullptr);
    ~OllamaModelCreateFromExistingModelWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldEmitCancelSignal();
    void shouldEmitCreateSignal();
    void shouldChangeCreateButtonEnableState();
};
