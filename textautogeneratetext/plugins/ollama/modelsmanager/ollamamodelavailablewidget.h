/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "ollamamodelavailableinfo.h"
#include "textautogenerateollama_private_export.h"
#include <QWidget>
class OllamaModelAvailableSearchWidget;
class OllamaModelAvailableListView;
class OllamaModelAvailableInfoWidget;
class OllamaModelAvailableInfosSortProxyModel;
class OllamaModelDownloadProgressWidget;
class QStackedWidget;
class OllamaManager;
class QScrollArea;
class OllamaModelAvailableInfosModel;
class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelAvailableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaModelAvailableWidget(OllamaManager *manager, QWidget *parent = nullptr);
    ~OllamaModelAvailableWidget() override;

    void setAvailableInfos(const QList<OllamaModelAvailableInfo> &infos);

private:
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void slotClicked(const QModelIndex &index);
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void slotDownloadModel(const QString &url);
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void slotAddModel();
    OllamaModelAvailableSearchWidget *const mSearchWidget;
    OllamaModelAvailableListView *const mListView;
    OllamaModelAvailableInfoWidget *const mInfoWidget;
    OllamaModelAvailableInfosSortProxyModel *const mProxyModel;
    OllamaModelDownloadProgressWidget *const mOllamaModelDownloadProgressWidget;
    QStackedWidget *const mStackedWidget;
    OllamaModelAvailableInfosModel *const mAvailableInfosModel;
    QScrollArea *const mScrollArea;
};
