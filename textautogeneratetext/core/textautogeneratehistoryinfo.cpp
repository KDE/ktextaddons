/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratehistoryinfo.h"

using namespace TextAutogenerateText;
TextAutoGenerateHistoryInfo::TextAutoGenerateHistoryInfo() = default;

TextAutoGenerateHistoryInfo::~TextAutoGenerateHistoryInfo() = default;

QDebug operator<<(QDebug d, const TextAutogenerateText::TextAutoGenerateHistoryInfo &t)
{
    d << "subject:" << t.subject();
    d << "datetime:" << t.dateTime();
    return d;
}

QString TextAutoGenerateHistoryInfo::subject() const
{
    return mSubject;
}

void TextAutoGenerateHistoryInfo::setSubject(const QString &newSubject)
{
    mSubject = newSubject;
}

qint64 TextAutoGenerateHistoryInfo::dateTime() const
{
    return mDateTime;
}

void TextAutoGenerateHistoryInfo::setDateTime(qint64 newDateTime)
{
    mDateTime = newDateTime;
}
