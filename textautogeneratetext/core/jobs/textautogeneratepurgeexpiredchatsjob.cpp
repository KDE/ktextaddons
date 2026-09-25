/*
 * SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "textautogeneratepurgeexpiredchatsjob.h"

using namespace TextAutoGenerateText;
TextAutoGeneratePurgeExpiredChatsJob::TextAutoGeneratePurgeExpiredChatsJob(QObject *parent)
    : QObject{parent}
{
}

TextAutoGeneratePurgeExpiredChatsJob::~TextAutoGeneratePurgeExpiredChatsJob() = default;
#include "moc_textautogeneratepurgeexpiredchatsjob.cpp"
