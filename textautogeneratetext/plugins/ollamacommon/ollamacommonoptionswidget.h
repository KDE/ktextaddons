/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "ollamacommonsettings.h"
#include "textautogenerateollamacommon_export.h"
#include <QWidget>
class QCheckBox;
class OllamaCommonShareNameComboBox;
class TEXTAUTOGENERATEOLLAMACOMMON_EXPORT OllamaCommonOptionsWidget : public QWidget
{
    Q_OBJECT
public:
    enum class ExtraOption : uint8_t {
        None = 0,
        ExposeToNetwork = 1,
    };
    Q_DECLARE_FLAGS(ExtraOptions, ExtraOption)
    Q_FLAG(ExtraOptions)

    struct OllamaCommonOptionsInfo {
        bool exposeToNetwork = false;
        bool thoughtProcessing = false;
        OllamaCommonSettings::ShareNameType shareNameType = OllamaCommonSettings::ShareNameType::DoNotShare;
    };

    explicit OllamaCommonOptionsWidget(ExtraOptions options = ExtraOptions(ExtraOption::None), QWidget *parent = nullptr);
    ~OllamaCommonOptionsWidget() override;

    [[nodiscard]] OllamaCommonOptionsInfo optionsInfo() const;
    void setOptionsInfo(const OllamaCommonOptionsInfo &info);

private:
    QCheckBox *const mExpose;
    QCheckBox *const mThoughtProcessing;
    const ExtraOptions mExtraOptions = ExtraOptions(ExtraOption::None);
    OllamaCommonShareNameComboBox *const mOllamaCommonShareNameComboBox;
};
Q_DECLARE_TYPEINFO(OllamaCommonOptionsWidget::OllamaCommonOptionsInfo, Q_RELOCATABLE_TYPE);
