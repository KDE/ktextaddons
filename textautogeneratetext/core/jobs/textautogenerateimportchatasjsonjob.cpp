/*
 * SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "textautogenerateimportchatasjsonjob.h"
#include <QFile>
using namespace TextAutoGenerateText;
TextAutoGenerateImportChatAsJsonJob::TextAutoGenerateImportChatAsJsonJob(QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateImportChatBaseJob{parent}
{
}

TextAutoGenerateImportChatAsJsonJob::~TextAutoGenerateImportChatAsJsonJob() = default;

void TextAutoGenerateImportChatAsJsonJob::importChat()
{
    // TODO
}
