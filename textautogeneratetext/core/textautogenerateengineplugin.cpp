/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateengineplugin.h"

using namespace TextAutogenerateText;
class TextAutogenerateText::TextAutogenerateEnginePluginPrivate
{
    // TODO
};

TextAutoGenerateEnginePlugin::TextAutoGenerateEnginePlugin(QObject *parent)
    : QObject{parent}
    , d(new TextAutogenerateText::TextAutogenerateEnginePluginPrivate)
{
}

TextAutoGenerateEnginePlugin::~TextAutoGenerateEnginePlugin() = default;

#include "moc_textautogenerateengineplugin.cpp"
