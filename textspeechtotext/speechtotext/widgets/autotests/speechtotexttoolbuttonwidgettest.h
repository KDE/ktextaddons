/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class SpeechToTextToolButtonWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit SpeechToTextToolButtonWidgetTest(QObject *parent = nullptr);
    ~SpeechToTextToolButtonWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};