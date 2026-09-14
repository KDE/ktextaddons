/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <QWidget>

class SpeechToTextGui : public QWidget
{
    Q_OBJECT
public:
    explicit SpeechToTextGui(QWidget *parent = nullptr);
    ~SpeechToTextGui() override;
};
