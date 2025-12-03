/*
 * SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "textautogenerateimportchatbasejob.h"
#include "textautogeneratetextcore_debug.h"
using namespace TextAutoGenerateText;
TextAutoGenerateImportChatBaseJob::TextAutoGenerateImportChatBaseJob(QObject *parent)
    : QObject{parent}
{
}

TextAutoGenerateImportChatBaseJob::~TextAutoGenerateImportChatBaseJob() = default;

TextAutoGenerateImportChatBaseJob::ImportChatInfo TextAutoGenerateImportChatBaseJob::info() const
{
    return mInfo;
}

void TextAutoGenerateImportChatBaseJob::setInfo(const ImportChatInfo &newInfo)
{
    mInfo = newInfo;
}

bool TextAutoGenerateImportChatBaseJob::canStart() const
{
    return mInfo.isValid();
}

void TextAutoGenerateImportChatBaseJob::start()
{
    if (!canStart()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << " Impossible to start job";
        deleteLater();
        return;
    }
    exportChat();
}

QDebug operator<<(QDebug d, const TextAutoGenerateImportChatBaseJob::ImportChatInfo &t)
{
    d.space() << "filename:" << t.filename;
    d.space() << "chatTitle:" << t.chatTitle;
    return d;
}

bool TextAutoGenerateImportChatBaseJob::ImportChatInfo::isValid() const
{
    return !filename.isEmpty();
}

#include "moc_textautogenerateimportchatbasejob.cpp"
