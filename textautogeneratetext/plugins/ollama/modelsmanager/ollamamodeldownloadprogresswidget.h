/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollama_private_export.h"
#include <QWidget>
class QProgressBar;
class QLabel;
class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelDownloadProgressWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaModelDownloadProgressWidget(QWidget *parent = nullptr);
    ~OllamaModelDownloadProgressWidget() override;

Q_SIGNALS:
    void cancelDownload();

private:
    QProgressBar *const mProgressBar;
    QLabel *const mModelName;
};
