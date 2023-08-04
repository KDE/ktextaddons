/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <TextTranslator/TranslatorEnginePlugin>
#include <TextTranslator/TranslatorUtil>
class BergamotEnginePlugin : public TextTranslator::TranslatorEnginePlugin
{
public:
    explicit BergamotEnginePlugin(QObject *parent = nullptr);
    ~BergamotEnginePlugin() override;

    void translate() override;

private:
    void loadSettings();
};
