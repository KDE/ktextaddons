/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollama_private_export.h"
#include <QWidget>
class QVBoxLayout;
class QLabel;
class OllamaNetworkUrlButton;
class OllamaManager;
class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelAvailableInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaModelAvailableInfoWidget(OllamaManager *manager, QWidget *parent = nullptr);
    ~OllamaModelAvailableInfoWidget() override;
    void generateWidget(const QModelIndex &index);

Q_SIGNALS:
    void downloadModel(const QString &url);

private:
    QVBoxLayout *const mMainLayout;
    QLabel *const mModelName;
    QWidget *mInfoWidget = nullptr;
    OllamaManager *const mOllamaManager;
    OllamaNetworkUrlButton *const mNetworkUrlButton;
};
