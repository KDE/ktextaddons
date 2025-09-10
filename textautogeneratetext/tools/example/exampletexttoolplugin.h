/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "core/tools/textautogeneratetexttoolplugin.h"

class ExampleTextToolPlugin : public TextAutoGenerateText::TextAutoGenerateTextToolPlugin
{
    Q_OBJECT
public:
    explicit ExampleTextToolPlugin(QObject *parent = nullptr);
    ~ExampleTextToolPlugin() override;
};
