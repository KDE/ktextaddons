/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "ollamamodelavailableinfo.h"
#include "textautogenerateollama_private_export.h"
#include <QWidget>
class OllamaModelInstalledListView;
class OllamaModelInstalledInfoWidget;
class OllamaManager;
class QToolButton;
namespace TextAutoGenerateText
{
class TextAutoGenerateModelSearchLineEdit;
}
class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelInstalledWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaModelInstalledWidget(OllamaManager *manager, QWidget *parent = nullptr);
    ~OllamaModelInstalledWidget() override;

    void setAvailableInfos(const QList<OllamaModelAvailableInfo> &infos);

private:
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void slotRemoveModel();
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void slotClicked(const QModelIndex &);
    QList<OllamaModelAvailableInfo> mModelAvailableInfos;
    OllamaModelInstalledListView *const mOllamaModelInstalledListView;
    TextAutoGenerateText::TextAutoGenerateModelSearchLineEdit *const mSearchLineEdit;
    QToolButton *const mRemoveModelButton;
    OllamaModelInstalledInfoWidget *const mOllamaModelInstalledInfoWidget;
    OllamaManager *const mManager;
};
