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
    QFile f(mInfo.filename);
    if (f.open(QFile::ReadOnly)) {
        const auto content = f.readAll();
        f.close();

        QJsonParseError error;
        const auto doc = QJsonDocument::fromJson(content, &error);
        // TODO verify error
    }
    // TODO
}
