/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautocorrectioncore_export.h"
#include <QChar>
class QDebug;
namespace TextAutoCorrectionCore
{
namespace AutoCorrectionUtils
{
struct TEXTAUTOCORRECTIONCORE_EXPORT TypographicQuotes {
    QChar begin;
    QChar end;
    [[nodiscard]] QString toString() const;
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] static TypographicQuotes fromString(const QString &str);
};

[[nodiscard]] TEXTAUTOCORRECTIONCORE_EXPORT TypographicQuotes typographicDefaultSingleQuotes();
[[nodiscard]] TEXTAUTOCORRECTIONCORE_EXPORT TypographicQuotes typographicDefaultDoubleQuotes();
[[nodiscard]] TEXTAUTOCORRECTIONCORE_EXPORT TypographicQuotes typographicDefaultFrenchQuotes();
[[nodiscard]] TEXTAUTOCORRECTIONCORE_EXPORT QString libreofficeFile(const QString &lang);
[[nodiscard]] TEXTAUTOCORRECTIONCORE_EXPORT QStringList libreOfficeAutoCorrectionPath();
[[nodiscard]] TEXTAUTOCORRECTIONCORE_EXPORT QStringList searchAutoCorrectLibreOfficeFiles();
[[nodiscard]] TEXTAUTOCORRECTIONCORE_EXPORT QStringList autoCorrectLibreOfficeLanguageToString(const QStringList &langs);
[[nodiscard]] TEXTAUTOCORRECTIONCORE_EXPORT QString libreOfficeWritableLocalAutoCorrectionPath();
[[nodiscard]] TEXTAUTOCORRECTIONCORE_EXPORT QString containsAutoCorrectionFile(const QString &lang,
                                                                               const QString &customSystemPath,
                                                                               const QString &customWritablePath);
[[nodiscard]] TEXTAUTOCORRECTIONCORE_EXPORT QString libreOfficeSystemPath();
[[nodiscard]] TEXTAUTOCORRECTIONCORE_EXPORT QString libreOfficeLocalPath();
[[nodiscard]] TEXTAUTOCORRECTIONCORE_EXPORT QStringList wordsFromSentence(const QString &string);
};
}
TEXTAUTOCORRECTIONCORE_EXPORT QDebug operator<<(QDebug d, TextAutoCorrectionCore::AutoCorrectionUtils::TypographicQuotes t);
