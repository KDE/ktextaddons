/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "bergamotenginesettingswidget.h"
#include "bergamotengineutils.h"
#include "libbergamot_export.h"
#include <QWidget>
class QTabWidget;
class BergamotEngineLanguageWidget;
class LIBBERGAMOT_EXPORT BergamotEngineWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BergamotEngineWidget(QWidget *parent = nullptr);
    ~BergamotEngineWidget() override;

    void setSettingsInfo(const BergamotEngineUtils::SettingsInfo &info);
    Q_REQUIRED_RESULT BergamotEngineUtils::SettingsInfo settingsInfo() const;

private:
    QTabWidget *const mTabWidget;
    BergamotEngineLanguageWidget *const mLanguageWidget;
    BergamotEngineSettingsWidget *const mSettingsWidget;
};
