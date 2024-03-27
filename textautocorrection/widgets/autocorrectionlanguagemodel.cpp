/*
  SPDX-FileCopyrightText: 2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrectionlanguagemodel.h"
#include <QLocale>

using namespace TextAutoCorrectionWidgets;
AutoCorrectionLanguageModel::AutoCorrectionLanguageModel(QObject *parent)
    : QAbstractListModel{parent}
{
    fillModel();
}

AutoCorrectionLanguageModel::~AutoCorrectionLanguageModel() = default;

int AutoCorrectionLanguageModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return mLocalInfos.count();
}

QString AutoCorrectionLanguageModel::language(int index) const
{
    return mLocalInfos.at(index).localeCode;
}

static bool stripCountryCode(QString *languageCode)
{
    const int idx = languageCode->indexOf(QLatin1Char('_'));
    if (idx != -1) {
        *languageCode = languageCode->left(idx);
        return true;
    }
    return false;
}

QVariant AutoCorrectionLanguageModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mLocalInfos.count()) {
        return {};
    }
    const LocaleInfo statusInfo = mLocalInfos.at(index.row());
    switch (role) {
    case Qt::DisplayRole:
    case LocaleI18n:
        return statusInfo.localeTranslated;
    case Locale:
        return statusInfo.localeCode;
    }
    return {};
}

void AutoCorrectionLanguageModel::fillModel()
{
    QLocale cLocale(QLocale::C);
    QSet<QString> insertedLanguages;
    const QList<QLocale> allLocales = QLocale::matchingLocales(QLocale::AnyLanguage, QLocale::AnyScript, QLocale::AnyTerritory);
    mLocalInfos.reserve(allLocales.count() + 1);
    for (const QLocale &lang : allLocales) {
        QString languageCode = lang.name();
        if (lang != cLocale) {
            // bug 484328 => don't translate locale name.
#if 0
            const QString nativeName = lang.nativeLanguageName();
            // For some languages the native name might be empty.
            // In this case use the non native language name as fallback.
            // See: QTBUG-51323
            QString languageName = nativeName.isEmpty() ? QLocale::languageToString(lang.language()) : nativeName;
#endif
            QString languageName = QLocale::languageToString(lang.language());
            languageName = languageName.toLower();
            if (!insertedLanguages.contains(languageName)) {
                LocaleInfo info;
                info.localeCode = languageCode;
                info.localeTranslated = languageName;
                mLocalInfos.append(std::move(info));
                insertedLanguages << languageName;
            } else if (stripCountryCode(&languageCode)) {
                if (!insertedLanguages.contains(languageName)) {
                    LocaleInfo info;
                    info.localeCode = languageCode;
                    info.localeTranslated = languageName;
                    mLocalInfos.append(std::move(info));
                    insertedLanguages << languageName;
                }
            }
        }
    }
}

#include "moc_autocorrectionlanguagemodel.cpp"
