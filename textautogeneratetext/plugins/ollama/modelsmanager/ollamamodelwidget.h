/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollama_private_export.h"
#include <QWidget>
class OllamaModelSearchWidget;
class OllamaModelListView;
class OllamaModelInfoWidget;
class OllamaModelInfosSortProxyModel;
class OllamaModelDownloadProgressWidget;
class QStackedWidget;
class OllamaManager;
class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaModelWidget(OllamaManager *manager, QWidget *parent = nullptr);
    ~OllamaModelWidget() override;

private:
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void slotClicked(const QModelIndex &index);
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void slotDownloadModel(const QString &url);
    OllamaModelSearchWidget *const mSearchWidget;
    OllamaModelListView *const mListView;
    OllamaModelInfoWidget *const mInfoWidget;
    OllamaModelInfosSortProxyModel *const mProxyModel;
    OllamaModelDownloadProgressWidget *const mOllamaModelDownloadProgressWidget;
    QStackedWidget *const mStackedWidget;
};
