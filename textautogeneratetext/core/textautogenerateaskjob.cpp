/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateaskjob.h"

using namespace TextAutoGenerateText;
TextAutoGenerateAskJob::TextAutoGenerateAskJob(QObject *parent)
    : QObject{parent}
{
}

TextAutoGenerateAskJob::~TextAutoGenerateAskJob() = default;

bool TextAutoGenerateAskJob::canStart() const
{
    // TODO
    return false;
}

void TextAutoGenerateAskJob::start()
{
    // TODO
    deleteLater();
}

#include "moc_textautogenerateaskjob.cpp"
