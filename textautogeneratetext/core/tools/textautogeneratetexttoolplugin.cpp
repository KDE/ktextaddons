/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetexttoolplugin.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextToolPlugin::TextAutoGenerateTextToolPlugin(QObject *parent)
    : QObject{parent}
{
}

TextAutoGenerateTextToolPlugin::~TextAutoGenerateTextToolPlugin() = default;

bool TextAutoGenerateTextToolPlugin::enabled() const
{
    return mEnabled;
}

void TextAutoGenerateTextToolPlugin::setEnabled(bool newEnabled)
{
    mEnabled = newEnabled;
}

QString TextAutoGenerateTextToolPlugin::toolName() const
{
    return mToolName;
}

void TextAutoGenerateTextToolPlugin::setToolName(const QString &newToolName)
{
    mToolName = newToolName;
}

void TextAutoGenerateTextToolPlugin::showConfigureDialog([[maybe_unused]] QWidget *parent) const
{
}

#include "moc_textautogeneratetexttoolplugin.cpp"
