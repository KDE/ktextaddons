/*
 * SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "textautogenerateexportchatbasejob.h"
#include "textautogeneratetextcore_debug.h"
using namespace TextAutoGenerateText;
TextAutoGenerateExportChatBaseJob::TextAutoGenerateExportChatBaseJob(QObject *parent)
    : QObject{parent}
{
}

TextAutoGenerateExportChatBaseJob::~TextAutoGenerateExportChatBaseJob() = default;

TextAutoGenerateExportChatBaseJob::ExportChatInfo TextAutoGenerateExportChatBaseJob::info() const
{
    return mInfo;
}

void TextAutoGenerateExportChatBaseJob::setInfo(const ExportChatInfo &newInfo)
{
    mInfo = newInfo;
}

bool TextAutoGenerateExportChatBaseJob::canStart() const
{
    return mInfo.isValid();
}

void TextAutoGenerateExportChatBaseJob::start()
{
    if (!canStart()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << " Impossible to start job";
        deleteLater();
        return;
    }
    exportChat();
}

QDebug operator<<(QDebug d, const TextAutoGenerateExportChatBaseJob::ExportChatInfo &t)
{
    d.space() << "filename:" << t.filename;
    d.space() << "chatTitle:" << t.chatTitle;
    d.space() << "listMessages:" << t.listMessages;
    return d;
}

bool TextAutoGenerateExportChatBaseJob::ExportChatInfo::isValid() const
{
    // TODO add more
    return !filename.isEmpty();
}

#include "moc_textautogenerateexportchatbasejob.cpp"
