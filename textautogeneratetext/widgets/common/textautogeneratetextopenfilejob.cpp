/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextopenfilejob.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextOpenFileJob::TextAutoGenerateTextOpenFileJob(QObject *parent)
    : TextAddonsWidgets::OpenFileJob{parent}
{
}

TextAutoGenerateTextOpenFileJob::~TextAutoGenerateTextOpenFileJob() = default;

void TextAutoGenerateTextOpenFileJob::downloadFile(const QUrl &fileUrl)
{
    // TODO
    deleteLater();
}

void TextAutoGenerateTextOpenFileJob::runApplication(const KService::Ptr &offer)
{
    // TODO
    deleteLater();
}

void TextAutoGenerateTextOpenFileJob::openUrl()
{
    // TODO
    deleteLater();
}

#include "moc_textautogeneratetextopenfilejob.cpp"
