/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class ManagerModelVoskSpeechToTextTest : public QObject
{
    Q_OBJECT
public:
    explicit ManagerModelVoskSpeechToTextTest(QObject *parent = nullptr);
    ~ManagerModelVoskSpeechToTextTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldLoadModelList_data();
    void shouldLoadModelList();
};
