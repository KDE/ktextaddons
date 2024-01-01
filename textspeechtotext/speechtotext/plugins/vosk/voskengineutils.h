/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "libvoskspeechtotext_export.h"
#include <QDebug>
#include <QString>

namespace VoskEngineUtils
{
[[nodiscard]] LIBVOSKSPEECHTOTEXT_EXPORT QString defaultVoskRepository();
[[nodiscard]] LIBVOSKSPEECHTOTEXT_EXPORT QString storageLanguagePath();

struct LIBVOSKSPEECHTOTEXT_EXPORT LanguageInstalled {
    QString name;
    QString absoluteLanguageModelPath;
    QString url;
    QString versionStr;
    [[nodiscard]] bool operator==(const LanguageInstalled &other) const;
    [[nodiscard]] bool isValid() const;
};

[[nodiscard]] LIBVOSKSPEECHTOTEXT_EXPORT VoskEngineUtils::LanguageInstalled loadInstalledLanguageInfo(const QString &modelInfoPath);

[[nodiscard]] LIBVOSKSPEECHTOTEXT_EXPORT bool createInstalledLanguageInfo(const QString &modelInfoPath, const LanguageInstalled &installed);

[[nodiscard]] LIBVOSKSPEECHTOTEXT_EXPORT QVector<LanguageInstalled> languageLocallyStored(const QString &path = {});

[[nodiscard]] LIBVOSKSPEECHTOTEXT_EXPORT QString defaultLanguage();

LIBVOSKSPEECHTOTEXT_EXPORT void saveSettings();
LIBVOSKSPEECHTOTEXT_EXPORT void loadSettings();
};
LIBVOSKSPEECHTOTEXT_EXPORT QDebug operator<<(QDebug d, const VoskEngineUtils::LanguageInstalled &t);
Q_DECLARE_TYPEINFO(VoskEngineUtils::LanguageInstalled, Q_MOVABLE_TYPE);
