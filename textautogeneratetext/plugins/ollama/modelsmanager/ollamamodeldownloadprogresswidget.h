/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollama_private_export.h"
#include <QWidget>
#include <TextAutoGenerateText/TextAutoGenerateReply>
class QProgressBar;
class QLabel;
class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelDownloadProgressWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaModelDownloadProgressWidget(QWidget *parent = nullptr);
    ~OllamaModelDownloadProgressWidget() override;

    void downloadModel(const QString &url);
Q_SIGNALS:
    void cancelDownload();

private:
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void slotDownloadProgressInfo(const TextAutoGenerateText::TextAutoGenerateReply::DownloadModelInfo &info);
    QProgressBar *const mProgressBar;
    QLabel *const mModelName;
    QLabel *const mProgressStatusLabel;
};
