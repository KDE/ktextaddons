/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollamacommon_export.h"
#include <QWidget>
#include <TextAutoGenerateText/TextAutoGenerateManager>
class QLabel;
class QVBoxLayout;
class OllamaCommonNetworkUrlButton;
class OllamaCommonModelAvailableInfo;

class TEXTAUTOGENERATEOLLAMACOMMON_EXPORT OllamaCommonModelAvailableInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaCommonModelAvailableInfoWidget(QWidget *parent = nullptr);
    ~OllamaCommonModelAvailableInfoWidget() override;

    void setOllamaModelAvailableInfo(const OllamaCommonModelAvailableInfo &info);

private:
    TEXTAUTOGENERATEOLLAMACOMMON_NO_EXPORT void changeFont(QLabel *label);
    TEXTAUTOGENERATEOLLAMACOMMON_NO_EXPORT void appendCategories(QStringList &lst,
                                                                 TextAutoGenerateText::TextAutoGenerateManager::Category cat,
                                                                 TextAutoGenerateText::TextAutoGenerateManager::Categories categories);
    QLabel *const mFamilyNameLabel;
    QLabel *const mParameterSizeLabel;
    QLabel *const mQuantizationLevelLabel;
    QLabel *const mModifiedAtLabel;
    QVBoxLayout *const mMainLayout;
    QWidget *mInfoWidget = nullptr;
    OllamaCommonNetworkUrlButton *const mNetworkUrlButton;
};
