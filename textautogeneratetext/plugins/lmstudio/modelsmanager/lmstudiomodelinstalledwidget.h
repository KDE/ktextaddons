/*
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratelmstudio_private_export.h"
#include <QWidget>
namespace TextAutoGenerateText
{
class TextAutoGenerateModelSearchLineEdit;
class TextAutoGenerateModelAvailableListView;
}
class LMStudioManager;
class LMStudioModelInstalledInfosModel;
class LMStudioModelInstalledInfosSortProxyModel;
class LMStudioModelInstalledInfoWidget;
class TEXTAUTOGENERATELMSTUDIO_TESTS_EXPORT LMStudioModelInstalledWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LMStudioModelInstalledWidget(LMStudioManager *manager, QWidget *parent = nullptr);
    ~LMStudioModelInstalledWidget() override;

private:
    TextAutoGenerateText::TextAutoGenerateModelAvailableListView *const mInstalledListView;
    TextAutoGenerateText::TextAutoGenerateModelSearchLineEdit *const mSearchLineEdit;
    LMStudioModelInstalledInfosModel *const mInstalledInfosModel;
    LMStudioModelInstalledInfosSortProxyModel *const mProxyModel;
    LMStudioModelInstalledInfoWidget *const mInstalledInfoWidget;
    LMStudioManager *const mManager;
};
