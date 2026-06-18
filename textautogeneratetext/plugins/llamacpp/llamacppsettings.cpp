/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "llamacppsettings.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <QDebug>
#include <QProcessEnvironment>

using namespace Qt::Literals::StringLiterals;

LLamaCppSettings::LLamaCppSettings() = default;

LLamaCppSettings::~LLamaCppSettings() = default;

QDebug operator<<(QDebug d, const LLamaCppSettings &t)
{
    d.space() << "displayName:" << t.displayName();
    d.space() << "currentModel:" << t.currentModel();
    return d;
}

void LLamaCppSettings::load(const KConfigGroup &config)
{
    setDisplayName(config.readEntry(u"Name"_s));
    setCurrentModel(config.readEntry(u"CurrentModel"_s));
}

void LLamaCppSettings::save(KConfigGroup &config)
{
    config.writeEntry(u"Name"_s, displayName());
    config.writeEntry(u"CurrentModel"_s, currentModel());
}

bool LLamaCppSettings::operator==(const LLamaCppSettings &other) const
{
    return other.mDisplayName == mDisplayName && other.mCurrentModel == mCurrentModel;
}

#include "moc_llamacppsettings.cpp"
