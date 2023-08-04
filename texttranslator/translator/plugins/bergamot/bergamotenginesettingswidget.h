/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>
class QComboBox;
class BergamotEngineSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BergamotEngineSettingsWidget(QWidget *parent = nullptr);
    ~BergamotEngineSettingsWidget() override;

private:
    QComboBox *const mNumberThreads;
    QComboBox *const mMemoryByThreads;
};
