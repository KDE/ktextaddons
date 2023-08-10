/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "libbergamot_export.h"
#include <QDir>
#include <QString>

namespace BergamotEngineUtils
{
Q_REQUIRED_RESULT LIBBERGAMOT_EXPORT QString defaultBergamotRepository();
Q_REQUIRED_RESULT LIBBERGAMOT_EXPORT QString groupName();
Q_REQUIRED_RESULT LIBBERGAMOT_EXPORT QString coreNumberKey();
Q_REQUIRED_RESULT LIBBERGAMOT_EXPORT QString memoryByThreadKey();
Q_REQUIRED_RESULT LIBBERGAMOT_EXPORT QString storageLanguagePath();

struct LIBBERGAMOT_EXPORT LanguageInstalled {
    QString from;
    QString to;
    QString shortName;
    QString absoluteLanguageModelPath;
    Q_REQUIRED_RESULT bool operator==(const LanguageInstalled &other) const;
};

Q_REQUIRED_RESULT LIBBERGAMOT_EXPORT QVector<LanguageInstalled> languageLocallyStored(const QString &path = {});
struct LIBBERGAMOT_EXPORT SettingsInfo {
    void loadSettingsInfo();
    void saveSettingsInfo();

    int numberOfThread = 0;
    int memoryByThread = 64;
};
// TODO add convert language to enum methods.
};

LIBBERGAMOT_EXPORT QDebug operator<<(QDebug d, const BergamotEngineUtils::LanguageInstalled &t);
Q_DECLARE_TYPEINFO(BergamotEngineUtils::LanguageInstalled, Q_MOVABLE_TYPE);
