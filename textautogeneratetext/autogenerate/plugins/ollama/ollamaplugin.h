/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "core/textautogeneratetextplugin.h"

class OllamaPlugin : public TextAutogenerateText::TextAutogenerateTextPlugin
{
    Q_OBJECT
public:
    explicit OllamaPlugin(QObject *parent = nullptr);
    ~OllamaPlugin() override;

    [[nodiscard]] bool loadSettings() override;
    void clear() override;
    [[nodiscard]] QString result() override;
};
