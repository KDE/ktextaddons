/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesettings.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KUser>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateSettings::TextAutoGenerateSettings()
{
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
    KConfigGroup myGroupUi(KSharedConfig::openStateConfig(), u"General"_s);
    myGroupUi.writeEntry("systemPrompt", mSystemPrompt);
    myGroupUi.sync();
}

void TextAutoGenerateSettings::load()
{
    const KUser user;
    const QString prompt = i18n(
        "You are an AI assistant. You are speaking to a person named %1. "
        "Be helpful, professional, and courteous. Do not give inaccurate "
        "information.",
        user.property(KUser::UserProperty::FullName).toString());

    const KConfigGroup myGroupUi(KSharedConfig::openStateConfig(), u"General"_s);
    mSystemPrompt = myGroupUi.readEntry("systemPrompt", prompt);
}
