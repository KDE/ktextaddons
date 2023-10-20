/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "libvoskspeechtotext_export.h"
#include <QDebug>
#include <QString>

namespace VoskEngineUtils
{
Q_REQUIRED_RESULT LIBVOSKSPEECHTOTEXT_EXPORT QString defaultVoskRepository();
Q_REQUIRED_RESULT LIBVOSKSPEECHTOTEXT_EXPORT QString storageLanguagePath();

struct LIBVOSKSPEECHTOTEXT_EXPORT LanguageInstalled {
    QString name;
    QString absoluteLanguageModelPath;
    QString url;
    QString versionStr;
    Q_REQUIRED_RESULT bool operator==(const LanguageInstalled &other) const;
    Q_REQUIRED_RESULT bool isValid() const;
};

Q_REQUIRED_RESULT LIBVOSKSPEECHTOTEXT_EXPORT VoskEngineUtils::LanguageInstalled loadInstalledLanguageInfo(const QString &modelInfoPath);

Q_REQUIRED_RESULT LIBVOSKSPEECHTOTEXT_EXPORT bool createInstalledLanguageInfo(const QString &modelInfoPath, const LanguageInstalled &installed);

Q_REQUIRED_RESULT LIBVOSKSPEECHTOTEXT_EXPORT QVector<LanguageInstalled> languageLocallyStored(const QString &path = {});

Q_REQUIRED_RESULT LIBVOSKSPEECHTOTEXT_EXPORT QString defaultLanguage();

LIBVOSKSPEECHTOTEXT_EXPORT void saveSettings();
LIBVOSKSPEECHTOTEXT_EXPORT void loadSettings();
};
LIBVOSKSPEECHTOTEXT_EXPORT QDebug operator<<(QDebug d, const VoskEngineUtils::LanguageInstalled &t);
Q_DECLARE_TYPEINFO(VoskEngineUtils::LanguageInstalled, Q_MOVABLE_TYPE);
