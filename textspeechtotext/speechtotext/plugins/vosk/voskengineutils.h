/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "libvoskspeechtotext_export.h"
class QDebug;
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

[[nodiscard]] LIBVOSKSPEECHTOTEXT_EXPORT QString groupName();
[[nodiscard]] LIBVOSKSPEECHTOTEXT_EXPORT QString activeLanguageKey();

[[nodiscard]] LIBVOSKSPEECHTOTEXT_EXPORT QString loadActiveLanguage();
LIBVOSKSPEECHTOTEXT_EXPORT void saveActiveLanguage(const QString &name);

/*!
 * Absolute path of the model directory to hand over to vosk, or an empty string
 * when no language is active or when the active one is not installed (anymore).
 */
[[nodiscard]] LIBVOSKSPEECHTOTEXT_EXPORT QString activeLanguageModelPath();
}
LIBVOSKSPEECHTOTEXT_EXPORT QDebug operator<<(QDebug d, const VoskEngineUtils::LanguageInstalled &t);
Q_DECLARE_TYPEINFO(VoskEngineUtils::LanguageInstalled, Q_RELOCATABLE_TYPE);
