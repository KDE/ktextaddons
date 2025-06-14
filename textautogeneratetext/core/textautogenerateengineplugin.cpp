/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateengineplugin.h"

using namespace TextAutoGenerateText;
class TextAutoGenerateText::TextAutoGenerateEnginePluginPrivate
{
    // TODO
};

TextAutoGenerateEnginePlugin::TextAutoGenerateEnginePlugin(QObject *parent)
    : QObject{parent}
    , d(new TextAutoGenerateText::TextAutoGenerateEnginePluginPrivate)
{
}

TextAutoGenerateEnginePlugin::~TextAutoGenerateEnginePlugin() = default;

void TextAutoGenerateEnginePlugin::load()
{
    // TODO
}

void TextAutoGenerateEnginePlugin::save()
{
    // TODO
}

#include "moc_textautogenerateengineplugin.cpp"
