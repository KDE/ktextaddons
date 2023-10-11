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
    QString versionStr;
    Q_REQUIRED_RESULT bool operator==(const LanguageInstalled &other) const;
};

LIBVOSKSPEECHTOTEXT_EXPORT void createInstalledLanguageInfo();

Q_REQUIRED_RESULT LIBVOSKSPEECHTOTEXT_EXPORT QVector<LanguageInstalled> languageLocallyStored(const QString &path = {});
};
LIBVOSKSPEECHTOTEXT_EXPORT QDebug operator<<(QDebug d, const VoskEngineUtils::LanguageInstalled &t);
Q_DECLARE_TYPEINFO(VoskEngineUtils::LanguageInstalled, Q_MOVABLE_TYPE);
