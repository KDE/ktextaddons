/*
  SPDX-FileCopyrightText: 2012-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "autocorrectionsettings.h"
#include "textautocorrectioncore_export.h"
#include <QTextCursor>

namespace TextAutoCorrection
{
class AutoCorrectionPrivate;
/**
 * @brief The AutoCorrection class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOCORRECTIONCORE_EXPORT AutoCorrection
{
public:
    AutoCorrection();
    ~AutoCorrection();

    void writeConfig();
    void readConfig();

    bool autocorrect(bool htmlMode, QTextDocument &document, int &position);

    void loadGlobalFileName(const QString &fname);

    Q_REQUIRED_RESULT AutoCorrectionSettings *autoCorrectionSettings() const;
    void setAutoCorrectionSettings(AutoCorrectionSettings *newAutoCorrectionSettings);

    void writeAutoCorrectionXmlFile(const QString &filename);

private:
    TEXTAUTOCORRECTIONCORE_NO_EXPORT void fixTwoUppercaseChars();
    Q_REQUIRED_RESULT TEXTAUTOCORRECTIONCORE_NO_EXPORT bool singleSpaces() const;
    TEXTAUTOCORRECTIONCORE_NO_EXPORT void capitalizeWeekDays();
    Q_REQUIRED_RESULT TEXTAUTOCORRECTIONCORE_NO_EXPORT bool autoFractions() const;
    TEXTAUTOCORRECTIONCORE_NO_EXPORT void uppercaseFirstCharOfSentence();
    Q_REQUIRED_RESULT TEXTAUTOCORRECTIONCORE_NO_EXPORT int advancedAutocorrect();
    TEXTAUTOCORRECTIONCORE_NO_EXPORT void replaceTypographicQuotes();
    TEXTAUTOCORRECTIONCORE_NO_EXPORT void superscriptAppendix();
    TEXTAUTOCORRECTIONCORE_NO_EXPORT void addNonBreakingSpace();

    TEXTAUTOCORRECTIONCORE_NO_EXPORT void selectPreviousWord(QTextCursor &cursor, int cursorPosition);
    TEXTAUTOCORRECTIONCORE_NO_EXPORT void selectStringOnMaximumSearchString(QTextCursor &cursor, int cursorPosition);

    Q_REQUIRED_RESULT TEXTAUTOCORRECTIONCORE_NO_EXPORT bool autoFormatURLs();
    Q_REQUIRED_RESULT TEXTAUTOCORRECTIONCORE_NO_EXPORT bool autoBoldUnderline();

    Q_REQUIRED_RESULT TEXTAUTOCORRECTIONCORE_NO_EXPORT QString autoDetectURL(const QString &_word) const;
    Q_REQUIRED_RESULT TEXTAUTOCORRECTIONCORE_NO_EXPORT bool excludeToUppercase(const QString &word) const;
    Q_REQUIRED_RESULT TEXTAUTOCORRECTIONCORE_NO_EXPORT QColor linkColor();
    friend class AutoCorrectionPrivate;
    std::unique_ptr<AutoCorrectionPrivate> const d;
};
}
