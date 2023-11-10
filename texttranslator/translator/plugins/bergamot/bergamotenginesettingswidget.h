/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "bergamotengineutils.h"
#include "libbergamot_private_export.h"

#include <QWidget>
class QComboBox;
class QCheckBox;
class LIBBERGAMOT_TESTS_EXPORT BergamotEngineSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BergamotEngineSettingsWidget(QWidget *parent = nullptr);
    ~BergamotEngineSettingsWidget() override;

    void setSettingsInfo(const BergamotEngineUtils::SettingsInfo &info);
    [[nodiscard]] BergamotEngineUtils::SettingsInfo settingsInfo() const;

private:
    void fillCombobox();
    QComboBox *const mNumberThreads;
    QComboBox *const mMemoryByThreads;
    QCheckBox *const mUseLocalCache;
};
