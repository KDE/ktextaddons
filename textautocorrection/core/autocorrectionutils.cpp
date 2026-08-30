/*
  SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrectionutils.h"

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QStandardPaths>
using namespace TextAutoCorrectionCore;
using namespace Qt::Literals::StringLiterals;
AutoCorrectionUtils::TypographicQuotes AutoCorrectionUtils::typographicDefaultSingleQuotes()
{
    TypographicQuotes quote;
    quote.begin = QChar(0x2018);
    quote.end = QChar(0x2019);
    return quote;
}

AutoCorrectionUtils::TypographicQuotes AutoCorrectionUtils::typographicDefaultDoubleQuotes()
{
    TypographicQuotes quote;
    quote.begin = QChar(0x201c);
    quote.end = QChar(0x201d);
    return quote;
}

AutoCorrectionUtils::TypographicQuotes AutoCorrectionUtils::typographicDefaultFrenchQuotes()
{
    TypographicQuotes quote;
    quote.begin = QChar(0x00AB);
    quote.end = QChar(0x00BB);
    return quote;
}

QDebug operator<<(QDebug d, TextAutoCorrectionCore::AutoCorrectionUtils::TypographicQuotes t)
{
    d << "TypographicQuotes.begin " << t.begin;
    d << "TypographicQuotes.end " << t.end;
    return d;
}

QString AutoCorrectionUtils::libreofficeFile(const QString &lang)
{
    return u"acor_%1.dat"_s.arg(lang);
}

QStringList AutoCorrectionUtils::libreOfficeAutoCorrectionPath()
{
    QStringList dirList;
    auto maybeAddPath = [&dirList](const QString &path) {
        if (QFileInfo::exists(path)) {
            dirList.append(path);
        }
    };
    maybeAddPath(libreOfficeWritableLocalAutoCorrectionPath());
    maybeAddPath(libreOfficeSystemPath());
    return dirList;
}

QString AutoCorrectionUtils::libreOfficeSystemPath()
{
#ifdef Q_OS_WIN
    return u"c:/Program Files/LibreOffice/share/autocorr/"_s;
#else
#ifdef Q_OS_MACOS
    return u"/Applications/LibreOffice.app/Contents/Resources/autocorr"_s;
#else
    return u"/usr/lib64/libreoffice/share/autocorr/"_s;
#endif
#endif
}

QString AutoCorrectionUtils::libreOfficeLocalPath()
{
#ifdef Q_OS_MACOS
    // It seems that they don't use lowercase
    return u"/LibreOffice/4/user/autocorr/"_s;
#else
    return u"/libreoffice/4/user/autocorr/"_s;
#endif
}

QString AutoCorrectionUtils::libreOfficeWritableLocalAutoCorrectionPath()
{
#ifdef Q_OS_WIN
    const QString writeablePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).remove(QCoreApplication::applicationName() + u'/')
        + AutoCorrectionUtils::libreOfficeLocalPath();
    return writeablePath;
#else
#ifdef Q_OS_MACOS
    // $HOME/Library/Application Support/OpenOffice/4/user/autocorr
    const QString writeablePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).remove(QCoreApplication::applicationName() + u'/')
        + AutoCorrectionUtils::libreOfficeLocalPath();
    return writeablePath;
#else
    return QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + libreOfficeLocalPath();
#endif
#endif
}

QStringList AutoCorrectionUtils::searchAutoCorrectLibreOfficeFiles()
{
    QStringList files;
    if (const QString path = libreOfficeSystemPath(); QFileInfo::exists(path)) {
        const QDir dir(path);
        const QStringList entryList = dir.entryList(QDir::Files | QDir::NoDotAndDotDot);
        for (const QString &file : entryList) {
            QString curFile = file;
            curFile.remove(path);
            curFile.remove(u".dat"_s);
            curFile.remove(u"acor_"_s);
            files.append(curFile);
        }
    }
    return files;
}

QStringList AutoCorrectionUtils::autoCorrectLibreOfficeLanguageToString(const QStringList &langs)
{
    QStringList languagesStr;
    const QList<QLocale> allLocales = QLocale::matchingLocales(QLocale::AnyLanguage, QLocale::AnyScript, QLocale::AnyCountry);
    for (const QLocale &locale : allLocales) {
        const QString languageCode = locale.name();
        for (const QString &lang : langs) {
            if (languageCode == lang) {
                const QString nativeName = locale.nativeLanguageName();
                // For some languages the native name might be empty.
                // In this case use the non native language name as fallback.
                // See: QTBUG-51323
                const QString languageName = nativeName.isEmpty() ? QLocale::languageToString(locale.language()) : nativeName;
                languagesStr.append(languageName);
                break;
            } else {
                QString b = lang;
                b.replace(u'-', u'_');
                if (languageCode == b) {
                    const QString nativeName = locale.nativeLanguageName();
                    // For some languages the native name might be empty.
                    // In this case use the non native language name as fallback.
                    // See: QTBUG-51323
                    const QString languageName = nativeName.isEmpty() ? QLocale::languageToString(locale.language()) : nativeName;
                    languagesStr.append(languageName);
                    break;
                }
            }
        }
    }
    return languagesStr;
}

QString AutoCorrectionUtils::TypographicQuotes::toString() const
{
    return begin + end;
}

bool AutoCorrectionUtils::TypographicQuotes::isEmpty() const
{
    return begin.isNull() && end.isNull();
}

AutoCorrectionUtils::TypographicQuotes AutoCorrectionUtils::TypographicQuotes::fromString(const QString &str)
{
    AutoCorrectionUtils::TypographicQuotes quotes;
    if (str.size() == 2) {
        quotes.begin = str.at(0);
        quotes.end = str.at(1);
    }
    return quotes;
}

QString AutoCorrectionUtils::containsAutoCorrectionFile(const QString &lang, const QString &customSystemPath, const QString &customWritablePath)
{
    QStringList libreOfficeAutocorrectPaths;
    if (!customWritablePath.isEmpty()) {
        libreOfficeAutocorrectPaths.append(customWritablePath);
    }
    if (!customSystemPath.isEmpty()) {
        libreOfficeAutocorrectPaths.append(customSystemPath);
    }
    libreOfficeAutocorrectPaths += AutoCorrectionUtils::libreOfficeAutoCorrectionPath();
    if (!libreOfficeAutocorrectPaths.isEmpty()) {
        QString fixLangExtension = lang;
        fixLangExtension.replace(u'_', u'-');
        for (const auto &path : std::as_const(libreOfficeAutocorrectPaths)) {
            // qDebug() << " filename " << filename;
            if (const QString filename = path + AutoCorrectionUtils::libreofficeFile(fixLangExtension); QFileInfo::exists(filename)) {
                return filename;
            }
        }
    }
    return {};
}

QStringList AutoCorrectionUtils::wordsFromSentence(const QString &string)
{
    QStringList lst;
    if (!string.trimmed().isEmpty()) {
        lst.append(string);
        QString tmpString = string;
        while (!tmpString.trimmed().isEmpty()) {
            bool foundStr = false;
            for (auto i = 0; i < tmpString.size(); i++) {
                if (tmpString.at(i).isSpace()) {
                    QString value;
                    const auto pos = tmpString.size() - i - 1;
                    value = tmpString.last(pos);
                    if (!value.trimmed().isEmpty()) {
                        lst.append(value);
                    }
                    tmpString = value;
                    foundStr = true;
                    break;
                }
            }
            if (!foundStr) {
                break;
            }
        }
    }
    return lst;
}
