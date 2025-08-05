/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesettings.h"
#include <KLocalizedString>
#include <KUser>

using namespace TextAutoGenerateText;
TextAutoGenerateSettings::TextAutoGenerateSettings()
{
    const KUser user;
    mSystemPrompt = i18n(
        "You are an AI assistant. You are speaking to a person named %1. "
        "Be helpful, professional, and courteous. Do not give inaccurate "
        "information.",
        user.property(KUser::UserProperty::FullName).toString());
}

TextAutoGenerateSettings::~TextAutoGenerateSettings() = default;

QString TextAutoGenerateSettings::systemPrompt() const
{
    return mSystemPrompt;
}

void TextAutoGenerateSettings::setSystemPrompt(const QString &newSystemPrompt)
{
    if (mSystemPrompt != newSystemPrompt) {
        mSystemPrompt = newSystemPrompt;
        save();
    }
}

void TextAutoGenerateSettings::save()
{
    // TODO
}

void TextAutoGenerateSettings::load()
{
    // TODO
}
