/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <QtWidgets/QWidget>

class ExampleTextToolPluginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ExampleTextToolPluginWidget(QWidget *parent = nullptr);
    ~ExampleTextToolPluginWidget() override;
};
