/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetexttoolpluginjob.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextToolPluginJob::TextAutoGenerateTextToolPluginJob(QObject *parent)
    : QObject{parent}
{
}

TextAutoGenerateTextToolPluginJob::~TextAutoGenerateTextToolPluginJob() = default;

void TextAutoGenerateTextToolPluginJob::start()
{
    // TODO
}

bool TextAutoGenerateTextToolPluginJob::canStart() const
{
    // TODO
    return false;
}

#include "moc_textautogeneratetexttoolpluginjob.cpp"
