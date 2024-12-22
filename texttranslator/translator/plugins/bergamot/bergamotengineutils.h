/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "libbergamot_export.h"
#include <QString>

namespace BergamotEngineUtils
{
[[nodiscard]] LIBBERGAMOT_EXPORT QString defaultBergamotRepository();
[[nodiscard]] LIBBERGAMOT_EXPORT QString groupName();
[[nodiscard]] LIBBERGAMOT_EXPORT QString coreNumberKey();
[[nodiscard]] LIBBERGAMOT_EXPORT QString memoryByThreadKey();
[[nodiscard]] LIBBERGAMOT_EXPORT QString storageLanguagePath();
[[nodiscard]] LIBBERGAMOT_EXPORT QString useLocalCacheKey();

struct LIBBERGAMOT_EXPORT LanguageInstalled {
    QString from;
    QString to;
    QString shortName;
    QString absoluteLanguageModelPath;
    int version = -1;
    [[nodiscard]] bool operator==(const LanguageInstalled &other) const;
};

[[nodiscard]] LIBBERGAMOT_EXPORT QVector<LanguageInstalled> languageLocallyStored(const QString &path = {});
struct LIBBERGAMOT_EXPORT SettingsInfo {
    void loadSettingsInfo();
    void saveSettingsInfo();

    int numberOfThread = 0;
    int memoryByThread = 64;
    bool useLocalCache = false;
};
};

LIBBERGAMOT_EXPORT QDebug operator<<(QDebug d, const BergamotEngineUtils::LanguageInstalled &t);
Q_DECLARE_TYPEINFO(BergamotEngineUtils::LanguageInstalled, Q_MOVABLE_TYPE);
