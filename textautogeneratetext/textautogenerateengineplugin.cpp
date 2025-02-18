/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateengineplugin.h"

using namespace TextAutogenerateText;
TextAutogenerateEnginePlugin::TextAutogenerateEnginePlugin(QObject *parent)
    : QObject{parent}
{
}

TextAutogenerateEnginePlugin::~TextAutogenerateEnginePlugin() = default;

#include "moc_textautogenerateengineplugin.cpp"
