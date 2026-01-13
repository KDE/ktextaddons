/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QWidget>

class OllamaOnlineConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaOnlineConfigureWidget(QWidget *parent = nullptr);
    ~OllamaOnlineConfigureWidget() override;
};
