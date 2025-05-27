/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QWidget>

class OllamaModelDownloadFromNameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaModelDownloadFromNameWidget(QWidget *parent = nullptr);
    ~OllamaModelDownloadFromNameWidget() override;
};
