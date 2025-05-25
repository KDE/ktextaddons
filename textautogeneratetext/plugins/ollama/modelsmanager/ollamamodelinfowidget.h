/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollama_private_export.h"
#include <QWidget>
class QVBoxLayout;
class QLabel;
class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaModelInfoWidget(QWidget *parent = nullptr);
    ~OllamaModelInfoWidget() override;
    void generateWidget(const QModelIndex &index);

Q_SIGNALS:
    void downloadModel(const QString &url);

private:
    QVBoxLayout *const mMainLayout;
    QLabel *const mModelName;
    QVBoxLayout *mDescriptionLayout = nullptr;
};
