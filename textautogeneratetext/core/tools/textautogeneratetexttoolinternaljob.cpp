/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetexttoolinternaljob.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextToolInternalJob::TextAutoGenerateTextToolInternalJob(QObject *parent)
    : TextAutoGenerateTextToolBaseJob(parent)
{
}

TextAutoGenerateTextToolInternalJob::~TextAutoGenerateTextToolInternalJob() = default;

void TextAutoGenerateTextToolInternalJob::start()
{
}

bool TextAutoGenerateTextToolInternalJob::canStart() const
{
    // TODO
    return true;
}
