/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextplugin.h"
using namespace TextAutogenerateText;

class TextAutogenerateText::TextAutogenerateTextPluginPrivate
{
public:
    bool hasError = false;
};

TextAutogenerateTextPlugin::TextAutogenerateTextPlugin(QObject *parent)
    : QObject{parent}
    , d(new TextAutogenerateText::TextAutogenerateTextPluginPrivate)
{
}

TextAutogenerateTextPlugin::~TextAutogenerateTextPlugin() = default;

void TextAutogenerateTextPlugin::setHasError(bool error)
{
    d->hasError = error;
}

#include "moc_textautogeneratetextplugin.cpp"
