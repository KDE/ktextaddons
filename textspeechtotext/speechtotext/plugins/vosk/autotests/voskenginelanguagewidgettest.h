/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class VoskEngineLanguageWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit VoskEngineLanguageWidgetTest(QObject *parent = nullptr);
    ~VoskEngineLanguageWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
