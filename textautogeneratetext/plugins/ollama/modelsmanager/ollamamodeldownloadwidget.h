/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogenerateollama_private_export.h"
#include <QWidget>
class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelDownloadWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaModelDownloadWidget(const QString &name, const QString &url, QWidget *parent = nullptr);
    ~OllamaModelDownloadWidget() override;
Q_SIGNALS:
    void downloadModel(const QString &url);
};
