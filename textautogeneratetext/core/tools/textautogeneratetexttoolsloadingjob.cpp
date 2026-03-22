/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetexttoolsloadingjob.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextToolsLoadingJob::TextAutoGenerateTextToolsLoadingJob(QObject *parent)
    : QObject{parent}
{
}

TextAutoGenerateTextToolsLoadingJob::~TextAutoGenerateTextToolsLoadingJob() = default;

void TextAutoGenerateTextToolsLoadingJob::start()
{
    if (!canStart()) {
        deleteLater();
        return;
    }
    // TODO
}

bool TextAutoGenerateTextToolsLoadingJob::canStart() const
{
    // TODO
    return true;
}

#include "moc_textautogeneratetexttoolsloadingjob.cpp"
