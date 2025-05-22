/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QWidget>
class OllamaModelSearchWidget;
class OllamaModelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaModelWidget(QWidget *parent = nullptr);
    ~OllamaModelWidget() override;

private:
    OllamaModelSearchWidget *const mSearchWidget;
};
