/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratechatsettings.h"

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateChatSettings::TextAutoGenerateChatSettings() = default;

TextAutoGenerateChatSettings::~TextAutoGenerateChatSettings() = default;

void TextAutoGenerateChatSettings::remove(const QByteArray &chatId)
{
    mPendingTypedTexts.remove(chatId);
}

void TextAutoGenerateChatSettings::add(const QByteArray &chatId, const PendingTypedInfo &info)
{
    mPendingTypedTexts[chatId] = info;
}

TextAutoGenerateChatSettings::PendingTypedInfo TextAutoGenerateChatSettings::value(const QByteArray &chatId)
{
    return mPendingTypedTexts.value(chatId);
}

bool TextAutoGenerateChatSettings::isEmpty() const
{
    return mPendingTypedTexts.isEmpty();
}

int TextAutoGenerateChatSettings::count() const
{
    return mPendingTypedTexts.count();
}

bool TextAutoGenerateChatSettings::PendingTypedInfo::isValid() const
{
    return !text.isEmpty() && (scrollbarPosition != -1);
}

QDebug operator<<(QDebug d, const TextAutoGenerateChatSettings::PendingTypedInfo &t)
{
    d.space() << "text" << t.text;
    d.space() << "scrollbarPosition" << t.scrollbarPosition;
    return d;
}
