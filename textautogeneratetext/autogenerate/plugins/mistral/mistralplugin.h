/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <textautogeneratetextplugin.h>

class MistralPlugin : public TextAutogenerateText::TextAutogenerateTextPlugin
{
    Q_OBJECT
public:
    explicit MistralPlugin(QObject *parent = nullptr);
    ~MistralPlugin() override;

    [[nodiscard]] bool loadSettings() override;
    void clear() override;
    [[nodiscard]] QString result() override;
};
