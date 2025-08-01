/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrectionsettings.h"
#include "export/exportlibreofficeautocorrection.h"
#include "import/importlibreofficeautocorrection.h"

#include "settings/textautocorrectionsettings.h"
#include "textautocorrection_debug.h"

#include <QRegularExpression>
#include <QStandardPaths>

using namespace TextAutoCorrectionCore;
using namespace Qt::Literals::StringLiterals;
namespace TextAutoCorrectionCore
{
class AutoCorrectionSettingsPrivate
{
public:
    AutoCorrectionUtils::TypographicQuotes mTypographicSingleQuotes;
    AutoCorrectionUtils::TypographicQuotes mTypographicDoubleQuotes;
    AutoCorrectionUtils::TypographicQuotes mDoubleFrenchQuotes;

    QHash<QString, QString> mAutocorrectEntries;
    QHash<QString, QString> mSuperScriptEntries;

    QSet<QString> mUpperCaseExceptions;
    QSet<QString> mTwoUpperLetterExceptions;

    QString mCustomWritablePath;
    QString mCustomSystemPath;

    QString mAutoCorrectLang;

    QChar mNonBreakingSpace;

    int mMaxFindStringLength = 0;
    int mMinFindStringLength = 0;

    bool mSingleSpaces = true; // suppress double spaces.
    bool mUppercaseFirstCharOfSentence = false; // convert first letter of a sentence automatically to uppercase
    bool mFixTwoUppercaseChars = false; // convert two uppercase characters to one upper and one lowercase.
    bool mAutoFractions = true; // replace 1/2 with ½
    bool mCapitalizeWeekDays = false;
    bool mAdvancedAutocorrect = false; // autocorrection from a list of entries

    bool mReplaceDoubleQuotes = false; // replace double quotes with typographical quotes
    bool mReplaceSingleQuotes = false; // replace single quotes with typographical quotes

    bool mAutoFormatUrl = false;
    bool mAutoBoldUnderline = false;
    bool mEnabled = false;
    bool mSuperScriptAppendix = false;

    bool mAddNonBreakingSpace = false;
    bool mReplaceDoubleQuotesByFrenchQuotes = false;
};
}

AutoCorrectionSettings::AutoCorrectionSettings()
    : d(new TextAutoCorrectionCore::AutoCorrectionSettingsPrivate)
{
    // default double quote open 0x201c
    // default double quote close 0x201d
    // default single quote open 0x2018
    // default single quote close 0x2019
    d->mTypographicSingleQuotes = AutoCorrectionUtils::typographicDefaultSingleQuotes();
    d->mTypographicDoubleQuotes = AutoCorrectionUtils::typographicDefaultDoubleQuotes();
    d->mDoubleFrenchQuotes = AutoCorrectionUtils::typographicDefaultFrenchQuotes();
    d->mNonBreakingSpace = QChar(QChar::Nbsp);
    readConfig();
}

AutoCorrectionSettings::~AutoCorrectionSettings() = default;

void AutoCorrectionSettings::setCapitalizeWeekDays(bool b)
{
    d->mCapitalizeWeekDays = b;
}

void AutoCorrectionSettings::setReplaceDoubleQuotes(bool b)
{
    d->mReplaceDoubleQuotes = b;
}

void AutoCorrectionSettings::setReplaceSingleQuotes(bool b)
{
    d->mReplaceSingleQuotes = b;
}

void AutoCorrectionSettings::setAdvancedAutocorrect(bool b)
{
    d->mAdvancedAutocorrect = b;
}

void AutoCorrectionSettings::setAutoFormatUrl(bool b)
{
    d->mAutoFormatUrl = b;
}

void AutoCorrectionSettings::setAutoBoldUnderline(bool b)
{
    d->mAutoBoldUnderline = b;
}

void AutoCorrectionSettings::setSuperScript(bool b)
{
    d->mSuperScriptAppendix = b;
}

void AutoCorrectionSettings::setAddNonBreakingSpace(bool b)
{
    d->mAddNonBreakingSpace = b;
}

bool AutoCorrectionSettings::isEnabledAutoCorrection() const
{
    return d->mEnabled;
}

bool AutoCorrectionSettings::isUppercaseFirstCharOfSentence() const
{
    return d->mUppercaseFirstCharOfSentence;
}

bool AutoCorrectionSettings::isFixTwoUppercaseChars() const
{
    return d->mFixTwoUppercaseChars;
}

bool AutoCorrectionSettings::isSingleSpaces() const
{
    return d->mSingleSpaces;
}

bool AutoCorrectionSettings::isAutoFractions() const
{
    return d->mAutoFractions;
}

bool AutoCorrectionSettings::isCapitalizeWeekDays() const
{
    return d->mCapitalizeWeekDays;
}

bool AutoCorrectionSettings::isReplaceDoubleQuotes() const
{
    return d->mReplaceDoubleQuotes;
}

bool AutoCorrectionSettings::isReplaceSingleQuotes() const
{
    return d->mReplaceSingleQuotes;
}

bool AutoCorrectionSettings::isAdvancedAutocorrect() const
{
    return d->mAdvancedAutocorrect;
}

bool AutoCorrectionSettings::isAutoFormatUrl() const
{
    return d->mAutoFormatUrl;
}

bool AutoCorrectionSettings::isAutoBoldUnderline() const
{
    return d->mAutoBoldUnderline;
}

bool AutoCorrectionSettings::isSuperScript() const
{
    return d->mSuperScriptAppendix;
}

bool AutoCorrectionSettings::isAddNonBreakingSpace() const
{
    return d->mAddNonBreakingSpace;
}

bool AutoCorrectionSettings::isReplaceDoubleQuotesByFrenchQuotes() const
{
    return d->mReplaceDoubleQuotesByFrenchQuotes;
}

void AutoCorrectionSettings::setEnabledAutoCorrection(bool b)
{
    d->mEnabled = b;
}

void AutoCorrectionSettings::setReplaceDoubleQuotesByFrenchQuotes(bool b)
{
    d->mReplaceDoubleQuotesByFrenchQuotes = b;
}

TextAutoCorrectionCore::AutoCorrectionUtils::TypographicQuotes AutoCorrectionSettings::typographicSingleQuotes() const
{
    return d->mTypographicSingleQuotes;
}

TextAutoCorrectionCore::AutoCorrectionUtils::TypographicQuotes AutoCorrectionSettings::typographicDoubleQuotes() const
{
    return d->mTypographicDoubleQuotes;
}

void AutoCorrectionSettings::setTypographicSingleQuotes(TextAutoCorrectionCore::AutoCorrectionUtils::TypographicQuotes singleQuote)
{
    d->mTypographicSingleQuotes = singleQuote;
}

void AutoCorrectionSettings::setTypographicDoubleQuotes(AutoCorrectionUtils::TypographicQuotes doubleQuote)
{
    d->mTypographicDoubleQuotes = doubleQuote;
}

void AutoCorrectionSettings::readConfig()
{
    d->mAutoBoldUnderline = TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->autoBoldUnderline();
    d->mAutoFormatUrl = TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->autoFormatUrl();
    d->mUppercaseFirstCharOfSentence = TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->uppercaseFirstCharOfSentence();
    d->mFixTwoUppercaseChars = TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->fixTwoUppercaseChars();
    d->mSingleSpaces = TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->singleSpaces();
    d->mAutoFractions = TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->autoFractions();
    d->mCapitalizeWeekDays = TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->capitalizeWeekDays();
    d->mAdvancedAutocorrect = TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->advancedAutocorrect();
    d->mReplaceDoubleQuotes = TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->replaceDoubleQuotes();
    d->mReplaceSingleQuotes = TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->replaceSingleQuotes();
    d->mEnabled = TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->enabled();
    d->mSuperScriptAppendix = TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->superScript();
    d->mAddNonBreakingSpace = TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->addNonBreakingSpaceInFrench();
    d->mReplaceDoubleQuotesByFrenchQuotes = TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->replaceDoubleQuotesByFrenchQuotes();
    d->mCustomSystemPath = TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->customSystemPath();
    d->mCustomWritablePath = TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->customWritablePath();

    d->mTypographicSingleQuotes =
        AutoCorrectionUtils::TypographicQuotes::fromString(TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->typographicSingleQuotes());
    if (d->mTypographicSingleQuotes.isEmpty()) {
        d->mTypographicSingleQuotes = AutoCorrectionUtils::typographicDefaultSingleQuotes();
    }
    d->mTypographicDoubleQuotes =
        AutoCorrectionUtils::TypographicQuotes::fromString(TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->typographicDoubleQuotes());
    if (d->mTypographicDoubleQuotes.isEmpty()) {
        d->mTypographicDoubleQuotes = AutoCorrectionUtils::typographicDefaultDoubleQuotes();
    }
    readAutoCorrectionFile();
}

void AutoCorrectionSettings::writeConfig()
{
    TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->setAutoBoldUnderline(d->mAutoBoldUnderline);
    TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->setAutoFormatUrl(d->mAutoFormatUrl);
    TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->setUppercaseFirstCharOfSentence(d->mUppercaseFirstCharOfSentence);
    TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->setFixTwoUppercaseChars(d->mFixTwoUppercaseChars);
    TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->setSingleSpaces(d->mSingleSpaces);
    TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->setAutoFractions(d->mAutoFractions);
    TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->setCapitalizeWeekDays(d->mCapitalizeWeekDays);
    TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->setAdvancedAutocorrect(d->mAdvancedAutocorrect);
    TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->setReplaceDoubleQuotes(d->mReplaceDoubleQuotes);
    TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->setReplaceSingleQuotes(d->mReplaceSingleQuotes);
    TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->setEnabled(d->mEnabled);
    TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->setSuperScript(d->mSuperScriptAppendix);
    TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->setAddNonBreakingSpaceInFrench(d->mAddNonBreakingSpace);
    TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->setTypographicSingleQuotes(d->mTypographicSingleQuotes.toString());
    TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->setTypographicDoubleQuotes(d->mTypographicDoubleQuotes.toString());
    TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->setReplaceDoubleQuotesByFrenchQuotes(d->mReplaceDoubleQuotesByFrenchQuotes);
    TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->setCustomWritablePath(d->mCustomWritablePath);
    TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->setCustomSystemPath(d->mCustomSystemPath);
    TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->requestSync();
    writeAutoCorrectionFile();
}

void AutoCorrectionSettings::setAutoFractions(bool newAutoFractions)
{
    d->mAutoFractions = newAutoFractions;
}

void AutoCorrectionSettings::setSingleSpaces(bool newSingleSpaces)
{
    d->mSingleSpaces = newSingleSpaces;
}

void AutoCorrectionSettings::setFixTwoUppercaseChars(bool newFixTwoUppercaseChars)
{
    d->mFixTwoUppercaseChars = newFixTwoUppercaseChars;
}

void AutoCorrectionSettings::setUppercaseFirstCharOfSentence(bool newUppercaseFirstCharOfSentence)
{
    d->mUppercaseFirstCharOfSentence = newUppercaseFirstCharOfSentence;
}

void AutoCorrectionSettings::setUpperCaseExceptions(const QSet<QString> &exceptions)
{
    d->mUpperCaseExceptions = exceptions;
}

void AutoCorrectionSettings::setTwoUpperLetterExceptions(const QSet<QString> &exceptions)
{
    d->mTwoUpperLetterExceptions = exceptions;
}

const QSet<QString> &AutoCorrectionSettings::upperCaseExceptions() const
{
    return d->mUpperCaseExceptions;
}

QSet<QString> AutoCorrectionSettings::twoUpperLetterExceptions() const
{
    return d->mTwoUpperLetterExceptions;
}

QString AutoCorrectionSettings::language() const
{
    return d->mAutoCorrectLang;
}

void AutoCorrectionSettings::setLanguage(const QString &lang, bool forceGlobal)
{
    if (d->mAutoCorrectLang != lang || forceGlobal) {
        d->mAutoCorrectLang = lang;
        // Re-read xml file
        readAutoCorrectionFile(forceGlobal);
    }
}

bool AutoCorrectionSettings::isFrenchLanguage() const
{
    return d->mAutoCorrectLang == "FR_fr"_L1 || d->mAutoCorrectLang == "fr"_L1;
}

bool AutoCorrectionSettings::addAutoCorrect(const QString &currentWord, const QString &replaceWord)
{
    if (!d->mAutocorrectEntries.contains(currentWord)) {
        d->mAutocorrectEntries.insert(currentWord, replaceWord);
        writeAutoCorrectionFile();
        return true;
    } else {
        return false;
    }
}

QChar AutoCorrectionSettings::nonBreakingSpace() const
{
    return d->mNonBreakingSpace;
}

void AutoCorrectionSettings::setNonBreakingSpace(const QChar &newNonBreakingSpace)
{
    d->mNonBreakingSpace = newNonBreakingSpace;
}

QHash<QString, QString> AutoCorrectionSettings::superScriptEntries() const
{
    return d->mSuperScriptEntries;
}

void AutoCorrectionSettings::setSuperScriptEntries(const QHash<QString, QString> &newSuperScriptEntries)
{
    d->mSuperScriptEntries = newSuperScriptEntries;
}

void AutoCorrectionSettings::setAutocorrectEntries(const QHash<QString, QString> &entries)
{
    d->mMaxFindStringLength = 0;
    d->mMinFindStringLength = 0;
    QHashIterator<QString, QString> i(entries);
    while (i.hasNext()) {
        i.next();
        const int findStringLenght(i.key().length());
        d->mMaxFindStringLength = qMax(d->mMaxFindStringLength, findStringLenght);
        d->mMinFindStringLength = qMin(d->mMinFindStringLength, findStringLenght);
    }
    d->mAutocorrectEntries = entries;
}

QHash<QString, QString> AutoCorrectionSettings::autocorrectEntries() const
{
    return d->mAutocorrectEntries;
}

void AutoCorrectionSettings::writeAutoCorrectionFile(const QString &filename)
{
    ExportLibreOfficeAutocorrection correct;
    correct.setAutocorrectEntries(d->mAutocorrectEntries);
    correct.setUpperCaseExceptions(d->mUpperCaseExceptions);
    correct.setTwoUpperLetterExceptions(d->mTwoUpperLetterExceptions);
    QString message;
    if (!correct.exportData(d->mAutoCorrectLang, filename, message, d->mCustomWritablePath)) {
        qCDebug(TEXTAUTOCORRECTION_LOG) << "We can't save in file :" << filename;
    }
}

int AutoCorrectionSettings::maxFindStringLength() const
{
    return d->mMaxFindStringLength;
}

int AutoCorrectionSettings::minFindStringLength() const
{
    return d->mMinFindStringLength;
}

void AutoCorrectionSettings::loadLocalFileName(const QString &localFileName, const QString &fname)
{
    ImportLibreOfficeAutocorrection import;
    QString messageError;
    if (import.import(localFileName, messageError, ImportAbstractAutocorrection::All)) {
        d->mUpperCaseExceptions = import.upperCaseExceptions();
        d->mTwoUpperLetterExceptions = import.twoUpperLetterExceptions();
        d->mAutocorrectEntries = import.autocorrectEntries();
        // Don't import it in local
        // mSuperScriptEntries = import.superScriptEntries();
    }
    if (!fname.isEmpty() && import.import(fname, messageError, ImportAbstractAutocorrection::SuperScript)) {
        d->mSuperScriptEntries = import.superScriptEntries();
    }
    d->mMaxFindStringLength = import.maxFindStringLenght();
    d->mMinFindStringLength = import.minFindStringLenght();
}

void AutoCorrectionSettings::loadGlobalFileName(const QString &fname)
{
    if (fname.isEmpty()) {
        const QString fileName = containsAutoCorrectionFile(d->mAutoCorrectLang);
        if (!fileName.isEmpty()) {
            QString errorMessage;
            ImportLibreOfficeAutocorrection import;
            if (import.import(fileName, errorMessage)) {
                d->mUpperCaseExceptions = import.upperCaseExceptions();
                d->mTwoUpperLetterExceptions = import.twoUpperLetterExceptions();
                d->mAutocorrectEntries = import.autocorrectEntries();
                d->mSuperScriptEntries = import.superScriptEntries();
                d->mMaxFindStringLength = import.maxFindStringLenght();
                d->mMinFindStringLength = import.minFindStringLenght();
            }
        }
    } else {
        qDebug() << " import libreoffice file " << fname;
        ImportLibreOfficeAutocorrection import;
        QString messageError;
        if (import.import(fname, messageError, ImportAbstractAutocorrection::All)) {
            d->mUpperCaseExceptions = import.upperCaseExceptions();
            d->mTwoUpperLetterExceptions = import.twoUpperLetterExceptions();
            d->mAutocorrectEntries = import.autocorrectEntries();
            d->mSuperScriptEntries = import.superScriptEntries();
            d->mMaxFindStringLength = import.maxFindStringLenght();
            d->mMinFindStringLength = import.minFindStringLenght();
        }
    }
}

void AutoCorrectionSettings::readAutoCorrectionFile(bool forceGlobal)
{
    d->mUpperCaseExceptions.clear();
    d->mAutocorrectEntries.clear();
    d->mTwoUpperLetterExceptions.clear();
    d->mSuperScriptEntries.clear();

    QString kdelang = u"en-US"_s;
    const QStringList lst = QLocale::system().uiLanguages();
    if (!lst.isEmpty()) {
        kdelang = lst.at(0);
        if (kdelang == u'C') {
            kdelang = u"en-US"_s;
        }
    }
    static const QRegularExpression reg(u"@.*"_s);
    kdelang.remove(reg);

    QString localFileName;
    static QRegularExpression regpath(QRegularExpression(u"_.*"_s));
    // Look at local file:
    if (!forceGlobal) {
        if (d->mAutoCorrectLang.isEmpty()) {
            if (!kdelang.isEmpty()) {
                localFileName = containsAutoCorrectionFile(kdelang);
            }
            if (localFileName.isEmpty() && kdelang.contains(u'_')) {
                kdelang.remove(regpath);
                localFileName = containsAutoCorrectionFile(kdelang);
            }
        }
    }
    QString fname;
    // Load Global directly
    if (!d->mAutoCorrectLang.isEmpty()) {
        localFileName = containsAutoCorrectionFile(d->mAutoCorrectLang);
    } else {
        if (fname.isEmpty() && !kdelang.isEmpty()) {
            fname = containsAutoCorrectionFile(kdelang);
        }
        if (fname.isEmpty() && kdelang.contains(u'_')) {
            kdelang.remove(regpath);
            fname = containsAutoCorrectionFile(kdelang);
        }
    }

    if (d->mAutoCorrectLang.isEmpty()) {
        d->mAutoCorrectLang = kdelang;
    }
    // qDebug() << " fname :" << fname;
    // qDebug() << " localFileName:" << localFileName;

    if (localFileName.isEmpty()) {
        loadGlobalFileName(fname);
    } else {
        loadLocalFileName(localFileName, fname);
    }
}

QString AutoCorrectionSettings::containsAutoCorrectionFile(const QString &fileName)
{
    return AutoCorrectionUtils::containsAutoCorrectionFile(fileName, d->mCustomSystemPath, d->mCustomWritablePath);
}

AutoCorrectionUtils::TypographicQuotes AutoCorrectionSettings::doubleFrenchQuotes() const
{
    return d->mDoubleFrenchQuotes;
}

void AutoCorrectionSettings::setDoubleFrenchQuotes(const AutoCorrectionUtils::TypographicQuotes &newDoubleFrenchQuotes)
{
    d->mDoubleFrenchQuotes = newDoubleFrenchQuotes;
}

QString AutoCorrectionSettings::customWritablePath() const
{
    return d->mCustomWritablePath;
}

void AutoCorrectionSettings::setCustomWritablePath(const QString &path)
{
    d->mCustomWritablePath = path;
}

QString AutoCorrectionSettings::customSystemPath() const
{
    return d->mCustomSystemPath;
}

void AutoCorrectionSettings::setCustomSystemPath(const QString &path)
{
    d->mCustomSystemPath = path;
}

QDebug operator<<(QDebug d, const TextAutoCorrectionCore::AutoCorrectionSettings &t)
{
    d << "mAddNonBreakingSpace " << t.nonBreakingSpace();
    d << "mSuperScriptAppendix " << t.isSuperScript();
    d << "mEnabled " << t.isEnabledAutoCorrection();
    d << "mAutoBoldUnderline " << t.isAutoBoldUnderline();
    d << "mAutoFormatUrl " << t.isAutoFormatUrl();
    d << "mReplaceSingleQuotes " << t.isReplaceSingleQuotes();
    d << "mReplaceDoubleQuotes " << t.isReplaceDoubleQuotes();
    d << "mAdvancedAutocorrect " << t.isAdvancedAutocorrect();
    d << "mCapitalizeWeekDays " << t.isCapitalizeWeekDays();
    d << "mAutoFractions " << t.isAutoFractions();
    d << "mFixTwoUppercaseChars " << t.isFixTwoUppercaseChars();
    d << "mUppercaseFirstCharOfSentence " << t.isUppercaseFirstCharOfSentence();
    d << "mSingleSpaces " << t.isSingleSpaces();
    d << "mMaxFindStringLength " << t.maxFindStringLength();
    d << "mMinFindStringLength " << t.minFindStringLength();
    d << "mNonBreakingSpace " << t.nonBreakingSpace();
    d << "mAutoCorrectLang " << t.language();
    d << "mTwoUpperLetterExceptions " << t.twoUpperLetterExceptions();
    d << "mUpperCaseExceptions " << t.upperCaseExceptions();
    d << "mSuperScriptEntries " << t.superScriptEntries();
    d << "mAutocorrectEntries " << t.autocorrectEntries();
    d << "mTypographicDoubleQuotes " << t.typographicDoubleQuotes();
    d << "mTypographicSingleQuotes " << t.typographicSingleQuotes();
    d << "mReplaceDoubleQuotesByFrenchQuotes " << t.isReplaceDoubleQuotesByFrenchQuotes();
    return d;
}
