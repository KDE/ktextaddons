/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "ollamacommonmodelavailableinfo.h"
#include "textautogenerateollama_private_export.h"
#include <QWidget>
class OllamaModelAvailableSearchWidget;
class OllamaModelAvailableListView;
class OllamaModelAvailableInfoWidget;
class OllamaCommonModelAvailableInfosSortProxyModel;
class OllamaModelDownloadProgressWidget;
class QStackedWidget;
class OllamaManager;
class QScrollArea;
class OllamaCommonModelAvailableInfosModel;
namespace TextAutoGenerateText
{
class TextAutoGenerateModelAvailableListView;
}
class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelAvailableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaModelAvailableWidget(OllamaManager *manager, QWidget *parent = nullptr);
    ~OllamaModelAvailableWidget() override;

    void setAvailableInfos(const QList<OllamaCommonModelAvailableInfo> &infos);

private:
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void slotClicked(const QModelIndex &index);
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void slotDownloadModel(const QString &url);
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void slotAddModel();
    OllamaModelAvailableSearchWidget *const mSearchWidget;
    TextAutoGenerateText::TextAutoGenerateModelAvailableListView *const mListView;
    OllamaModelAvailableInfoWidget *const mInfoWidget;
    OllamaCommonModelAvailableInfosSortProxyModel *const mProxyModel;
    OllamaModelDownloadProgressWidget *const mOllamaModelDownloadProgressWidget;
    QStackedWidget *const mStackedWidget;
    OllamaCommonModelAvailableInfosModel *const mAvailableInfosModel;
    QScrollArea *const mScrollArea;
};
