/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollamacommon_export.h"
#include <QWidget>
class QLabel;
class QVBoxLayout;
class OllamaCommonNetworkUrlButton;

class TEXTAUTOGENERATEOLLAMACOMMON_EXPORT OllamaCommonModelAvailableInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaCommonModelAvailableInfoWidget(QWidget *parent = nullptr);
    ~OllamaCommonModelAvailableInfoWidget() override;

#if 0
    void setOllamaModelInstalledInfo(const OllamaModelInstalledInfo &info);
#endif
private:
    TEXTAUTOGENERATEOLLAMACOMMON_NO_EXPORT void changeFont(QLabel *label);
#if 0
    TEXTAUTOGENERATEOLLAMACOMMON_NO_EXPORT void appendCategories(QStringList &lst,
                                                           TextAutoGenerateText::TextAutoGenerateManager::Category cat,
                                                           TextAutoGenerateText::TextAutoGenerateManager::Categories categories);
#endif
    QLabel *const mFamilyNameLabel;
    QLabel *const mParameterSizeLabel;
    QLabel *const mQuantizationLevelLabel;
    QLabel *const mModifiedAtLabel;
    QVBoxLayout *const mMainLayout;
    QWidget *mInfoWidget = nullptr;
    OllamaCommonNetworkUrlButton *const mNetworkUrlButton;
};
