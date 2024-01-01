/*
  SPDX-FileCopyrightText: 2022-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "autocorrectionutils.h"
#include "textautocorrectioncore_export.h"
#include <QDebug>
#include <QSet>
namespace TextAutoCorrectionCore
{
class AutoCorrectionSettingsPrivate;
class TEXTAUTOCORRECTIONCORE_EXPORT AutoCorrectionSettings
{
public:
    AutoCorrectionSettings();
    ~AutoCorrectionSettings();

    [[nodiscard]] bool isEnabledAutoCorrection() const;
    [[nodiscard]] bool isUppercaseFirstCharOfSentence() const;
    [[nodiscard]] bool isFixTwoUppercaseChars() const;
    [[nodiscard]] bool isSingleSpaces() const;
    [[nodiscard]] bool isAutoFractions() const;
    [[nodiscard]] bool isCapitalizeWeekDays() const;
    [[nodiscard]] bool isReplaceDoubleQuotes() const;
    [[nodiscard]] bool isReplaceSingleQuotes() const;
    [[nodiscard]] bool isAdvancedAutocorrect() const;
    [[nodiscard]] bool isAutoFormatUrl() const;
    [[nodiscard]] bool isAutoBoldUnderline() const;
    [[nodiscard]] bool isSuperScript() const;

    [[nodiscard]] bool isAddNonBreakingSpace() const;
    [[nodiscard]] bool isReplaceDoubleQuotesByFrenchQuotes() const;

    [[nodiscard]] TextAutoCorrectionCore::AutoCorrectionUtils::TypographicQuotes typographicSingleQuotes() const;
    [[nodiscard]] TextAutoCorrectionCore::AutoCorrectionUtils::TypographicQuotes typographicDoubleQuotes() const;
    void setTypographicSingleQuotes(TextAutoCorrectionCore::AutoCorrectionUtils::TypographicQuotes singleQuote);
    void setTypographicDoubleQuotes(TextAutoCorrectionCore::AutoCorrectionUtils::TypographicQuotes doubleQuote);

    void setAutoFormatUrl(bool b);
    void setAutoBoldUnderline(bool b);
    void setSuperScript(bool b);
    void setAddNonBreakingSpace(bool b);
    void setCapitalizeWeekDays(bool b);
    void setReplaceDoubleQuotes(bool b);
    void setReplaceSingleQuotes(bool b);
    void setAdvancedAutocorrect(bool b);
    void setEnabledAutoCorrection(bool b);
    void setReplaceDoubleQuotesByFrenchQuotes(bool b);

    void readConfig();

    void writeConfig();

    void setAutoFractions(bool newAutoFractions);

    void setSingleSpaces(bool newSingleSpaces);

    void setFixTwoUppercaseChars(bool newFixTwoUppercaseChars);

    void setUppercaseFirstCharOfSentence(bool newUppercaseFirstCharOfSentence);

    void setUpperCaseExceptions(const QSet<QString> &exceptions);
    void setTwoUpperLetterExceptions(const QSet<QString> &exceptions);
    [[nodiscard]] QSet<QString> upperCaseExceptions() const;
    [[nodiscard]] QSet<QString> twoUpperLetterExceptions() const;

    void setLanguage(const QString &lang, bool forceGlobal = false);
    [[nodiscard]] QString language() const;

    [[nodiscard]] bool isFrenchLanguage() const;
    void setAutocorrectEntries(const QHash<QString, QString> &entries);

    [[nodiscard]] QHash<QString, QString> autocorrectEntries() const;
    [[nodiscard]] bool addAutoCorrect(const QString &currentWord, const QString &replaceWord);

    [[nodiscard]] QChar nonBreakingSpace() const;
    void setNonBreakingSpace(const QChar &newNonBreakingSpace);

    [[nodiscard]] QHash<QString, QString> superScriptEntries() const;
    void setSuperScriptEntries(const QHash<QString, QString> &newSuperScriptEntries);

    void writeAutoCorrectionFile(const QString &filename = QString());
    [[nodiscard]] int maxFindStringLength() const;

    [[nodiscard]] int minFindStringLength() const;

    void loadLocalFileName(const QString &localFileName, const QString &fname);
    void loadGlobalFileName(const QString &fname);

    [[nodiscard]] AutoCorrectionUtils::TypographicQuotes doubleFrenchQuotes() const;
    void setDoubleFrenchQuotes(const AutoCorrectionUtils::TypographicQuotes &newDoubleFrenchQuotes);

    [[nodiscard]] QString customWritablePath() const;
    void setCustomWritablePath(const QString &path);

    [[nodiscard]] QString customSystemPath() const;
    void setCustomSystemPath(const QString &path);

private:
    TEXTAUTOCORRECTIONCORE_NO_EXPORT void migrateKMailXmlFile();
    TEXTAUTOCORRECTIONCORE_NO_EXPORT void readAutoCorrectionFile(bool forceGlobal = false);
    [[nodiscard]] TEXTAUTOCORRECTIONCORE_NO_EXPORT QString containsAutoCorrectionFile(const QString &fileName);

    friend class AutoCorrectionSettingsPrivate;
    std::unique_ptr<AutoCorrectionSettingsPrivate> const d;
};
}
TEXTAUTOCORRECTIONCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoCorrectionCore::AutoCorrectionSettings &t);
