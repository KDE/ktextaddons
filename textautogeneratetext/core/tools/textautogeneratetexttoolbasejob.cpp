/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetexttoolbasejob.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextToolBaseJob::TextAutoGenerateTextToolBaseJob(QObject *parent)
    : QObject{parent}
{
}

TextAutoGenerateTextToolBaseJob::~TextAutoGenerateTextToolBaseJob() = default;

#include "moc_textautogeneratetexttoolbasejob.cpp"
