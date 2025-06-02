/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "ollamamodelavailableinfo.h"
#include "ollamamodelinstalledinfo.h"
#include "textautogenerateollama_private_export.h"
#include <QWidget>
class QLabel;
class QVBoxLayout;
class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelInstalledInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaModelInstalledInfoWidget(QWidget *parent = nullptr);
    ~OllamaModelInstalledInfoWidget() override;

    void setOllamaModelInstalledInfo(const OllamaModelInstalledInfo &info, const QList<OllamaModelAvailableInfo> &infos);

private:
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void changeFont(QLabel *label);
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void
    appendCategories(QStringList &lst, OllamaModelAvailableInfo::Category cat, OllamaModelAvailableInfo::Categories categories);
    QLabel *const mFamilyNameLabel;
    QLabel *const mParameterSizeLabel;
    QLabel *const mQuantizationLevelLabel;
    QLabel *const mModifiedAtLabel;
    QVBoxLayout *const mMainLayout;
    QWidget *mInfoWidget = nullptr;
};
