/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextreplyinfo.h"
#include <QDebug>
QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextReplyInfo &t)
{
    d.space() << "totalDuration:" << t.totalDuration;
    d.space() << "loadDuration:" << t.loadDuration;
    d.space() << "promptEvalTokenCount:" << t.promptEvalTokenCount;
    d.space() << "promptEvalDuration:" << t.promptEvalDuration;
    d.space() << "tokenCount:" << t.tokenCount;
    d.space() << "duration:" << t.duration;
    return d;
}
