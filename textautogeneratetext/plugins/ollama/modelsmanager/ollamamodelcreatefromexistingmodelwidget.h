/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QWidget>

class OllamaModelCreateFromExistingModelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaModelCreateFromExistingModelWidget(QWidget *parent = nullptr);
    ~OllamaModelCreateFromExistingModelWidget() override;
};
