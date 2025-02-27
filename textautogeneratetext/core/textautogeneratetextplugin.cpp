/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextplugin.h"
using namespace TextAutogenerateText;

class TextAutogenerateText::TextAutogenerateTextPluginPrivate
{
};

TextAutogenerateTextPlugin::TextAutogenerateTextPlugin(QObject *parent)
    : QObject{parent}
    , d(new TextAutogenerateText::TextAutogenerateTextPluginPrivate)
{
}

TextAutogenerateTextPlugin::~TextAutogenerateTextPlugin() = default;

#include "moc_textautogeneratetextplugin.cpp"
