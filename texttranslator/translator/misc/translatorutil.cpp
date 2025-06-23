/*
  SPDX-FileCopyrightText: 2012-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "translatorutil.h"

#include "texttranslator_debug.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QComboBox>

using namespace Qt::Literals::StringLiterals;
using namespace TextTranslator;
TranslatorUtil::TranslatorUtil() = default;

QMap<TranslatorUtil::Language, QString> TranslatorUtil::translatedLanguages()
{
    QMap<TranslatorUtil::Language, QString> map;
    for (int i = TranslatorUtil::Language::automatic; i < TranslatorUtil::Language::lastLanguage; ++i) {
        map.insert(static_cast<TranslatorUtil::Language>(i), translatedLanguage(static_cast<TranslatorUtil::Language>(i)));
    }
    return map;
}

QString TranslatorUtil::translatedLanguage(TranslatorUtil::Language lang)
{
    QString ret;
    switch (lang) {
    case automatic:
        ret = i18n("Detect language");
        break;
    case hmong:
        ret = i18n("Hmong");
        break;
    case bs:
        ret = i18n("Bosnian");
        break;
    case en:
        ret = i18n("English");
        break;
    case zh:
        ret = i18n("Chinese (Simplified)");
        break;
    case zt:
        ret = i18n("Chinese (Traditional)");
        break;
    case nl:
        ret = i18n("Dutch");
        break;
    case fr:
        ret = i18n("French");
        break;
    case de:
        ret = i18n("German");
        break;
    case el:
        ret = i18n("Greek");
        break;
    case it:
        ret = i18n("Italian");
        break;
    case ja:
        ret = i18n("Japanese");
        break;
    case ko:
        ret = i18n("Korean");
        break;
    case pt:
        ret = i18n("Portuguese");
        break;
    case ru:
        ret = i18n("Russian");
        break;
    case es:
        ret = i18n("Spanish");
        break;
    case af:
        ret = i18n("Afrikaans");
        break;
    case sq:
        ret = i18n("Albanian");
        break;
    case ar:
        ret = i18n("Arabic");
        break;
    case hy:
        ret = i18n("Armenian");
        break;
    case az:
        ret = i18n("Azerbaijani");
        break;
    case eu:
        ret = i18n("Basque");
        break;
    case be:
        ret = i18n("Belarusian");
        break;
    case bg:
        ret = i18n("Bulgarian");
        break;
    case ca:
        ret = i18n("Catalan");
        break;
    case hr:
        ret = i18n("Croatian");
        break;
    case cs:
        ret = i18n("Czech");
        break;
    case da:
        ret = i18n("Danish");
        break;
    case et:
        ret = i18n("Estonian");
        break;
    case tl:
        ret = i18n("Filipino");
        break;
    case fi:
        ret = i18n("Finnish");
        break;
    case gl:
        ret = i18n("Galician");
        break;
    case ka:
        ret = i18n("Georgian");
        break;
    case ht:
        ret = i18n("Haitian Creole");
        break;
    case iw:
        ret = i18n("Hebrew");
        break;
    case hi:
        ret = i18n("Hindi");
        break;
    case hu:
        ret = i18n("Hungarian");
        break;
    case is:
        ret = i18n("Icelandic");
        break;
    case id:
        ret = i18n("Indonesian");
        break;
    case ga:
        ret = i18n("Irish");
        break;
    case lv:
        ret = i18n("Latvian");
        break;
    case lt:
        ret = i18n("Lithuanian");
        break;
    case mk:
        ret = i18n("Macedonian");
        break;
    case ms:
        ret = i18n("Malay");
        break;
    case mt:
        ret = i18n("Maltese");
        break;
    case no:
        ret = i18n("Norwegian");
        break;
    case fa:
        ret = i18n("Persian");
        break;
    case pl:
        ret = i18n("Polish");
        break;
    case ro:
        ret = i18n("Romanian");
        break;
    case sr:
        ret = i18n("Serbian");
        break;
    case sk:
        ret = i18n("Slovak");
        break;
    case sl:
        ret = i18n("Slovenian");
        break;
    case sw:
        ret = i18n("Swahili");
        break;
    case sv:
        ret = i18n("Swedish");
        break;
    case th:
        ret = i18n("Thai");
        break;
    case tr:
        ret = i18n("Turkish");
        break;
    case uk:
        ret = i18n("Ukrainian");
        break;
    case ur:
        ret = i18n("Urdu");
        break;
    case vi:
        ret = i18n("Vietnamese");
        break;
    case cy:
        ret = i18n("Welsh");
        break;
    case yi:
        ret = i18n("Yiddish");
        break;
    }
    return ret;
}

QString TranslatorUtil::searchI18nFromLanguage(const QString &langCode)
{
    for (int i = TranslatorUtil::Language::automatic; i < TranslatorUtil::Language::lastLanguage; ++i) {
        if (langCode == languageCode(static_cast<TranslatorUtil::Language>(i))) {
            return translatedLanguage(static_cast<TranslatorUtil::Language>(i));
        }
    }
    return {};
}

TranslatorUtil::Language TranslatorUtil::stringToLanguage(const QString &str)
{
    if (str == "en"_L1) {
        return TranslatorUtil::en;
    } else if (str == "fr"_L1) {
        return TranslatorUtil::fr;
    } else if (str == "es"_L1) {
        return TranslatorUtil::es;
    } else if (str == "pl"_L1) {
        return TranslatorUtil::pl;
    } else if (str == "de"_L1) {
        return TranslatorUtil::de;
    } else if (str == "cs"_L1) {
        return TranslatorUtil::cs;
    } else if (str == "bg"_L1) {
        return TranslatorUtil::bg;
    } else if (str == "et"_L1) {
        return TranslatorUtil::et;
        //    } else if (str == "nn"_L1) {
        //        return TranslatorUtil::nn;
    } else {
        qCWarning(TEXTTRANSLATOR_LOG) << " Impossible to find TranslatorUtil::Language for " << str;
    }
    return TranslatorUtil::en;
}

QString TranslatorUtil::languageCode(TranslatorUtil::Language lang)
{
    QString ret;
    switch (lang) {
    case automatic:
        ret = u"auto"_s;
        break;
    case hmong:
        ret = u"hmn"_s;
        break;
    case en:
        ret = u"en"_s;
        break;
    case zh:
        ret = u"zh-CN"_s;
        break;
    case zt:
        ret = u"zh-TW"_s;
        break;
    case nl:
        ret = u"nl"_s;
        break;
    case fr:
        ret = u"fr"_s;
        break;
    case de:
        ret = u"de"_s;
        break;
    case el:
        ret = u"el"_s;
        break;
    case it:
        ret = u"it"_s;
        break;
    case ja:
        ret = u"ja"_s;
        break;
    case ko:
        ret = u"ko"_s;
        break;
    case pt:
        ret = u"pt"_s;
        break;
    case ru:
        ret = u"ru"_s;
        break;
    case es:
        ret = u"es"_s;
        break;
    case af:
        ret = u"af"_s;
        break;
    case sq:
        ret = u"sq"_s;
        break;
    case ar:
        ret = u"ar"_s;
        break;
    case hy:
        ret = u"hy"_s;
        break;
    case az:
        ret = u"az"_s;
        break;
    case eu:
        ret = u"eu"_s;
        break;
    case be:
        ret = u"be"_s;
        break;
    case bg:
        ret = u"bg"_s;
        break;
    case ca:
        ret = u"ca"_s;
        break;
    case hr:
        ret = u"hr"_s;
        break;
    case cs:
        ret = u"cs"_s;
        break;
    case da:
        ret = u"da"_s;
        break;
    case et:
        ret = u"et"_s;
        break;
    case tl:
        ret = u"tl"_s;
        break;
    case fi:
        ret = u"fi"_s;
        break;
    case gl:
        ret = u"gl"_s;
        break;
    case ka:
        ret = u"ka"_s;
        break;
    case ht:
        ret = u"ht"_s;
        break;
    case iw:
        ret = u"he"_s;
        break;
    case hi:
        ret = u"hi"_s;
        break;
    case hu:
        ret = u"hu"_s;
        break;
    case is:
        ret = u"is"_s;
        break;
    case id:
        ret = u"id"_s;
        break;
    case ga:
        ret = u"ga"_s;
        break;
    case lv:
        ret = u"lv"_s;
        break;
    case lt:
        ret = u"lt"_s;
        break;
    case mk:
        ret = u"mk"_s;
        break;
    case ms:
        ret = u"ms"_s;
        break;
    case mt:
        ret = u"mt"_s;
        break;
    case no:
        ret = u"no"_s;
        break;
    case fa:
        ret = u"fa"_s;
        break;
    case pl:
        ret = u"pl"_s;
        break;
    case ro:
        ret = u"ro"_s;
        break;
    case sr:
        ret = u"sr"_s;
        break;
    case sk:
        ret = u"sk"_s;
        break;
    case sl:
        ret = u"sl"_s;
        break;
    case sw:
        ret = u"sw"_s;
        break;
    case sv:
        ret = u"sv"_s;
        break;
    case th:
        ret = u"th"_s;
        break;
    case tr:
        ret = u"tr"_s;
        break;
    case uk:
        ret = u"uk"_s;
        break;
    case ur:
        ret = u"ur"_s;
        break;
    case vi:
        ret = u"vi"_s;
        break;
    case cy:
        ret = u"cy"_s;
        break;
    case yi:
        ret = u"yi"_s;
        break;
    case bs:
        return u"bs"_s;
    }
    return ret;
}

void TranslatorUtil::addItemToFromComboBox(QComboBox *combo, const QString &languageCode, const QString &translatedStr)
{
    combo->addItem(translatedStr, languageCode);
}

QString TranslatorUtil::groupTranslateName()
{
    return u"Translate"_s;
}

QString TranslatorUtil::engineTranslateName()
{
    return u"engine"_s;
}

QString TranslatorUtil::defaultEngineName()
{
    return u"google"_s;
}

QString TranslatorUtil::loadEngine()
{
    KConfigGroup myGeneralGroup(KSharedConfig::openConfig(), groupTranslateName());
    const QString engineTypeStr = myGeneralGroup.readEntry(engineTranslateName(), defaultEngineName()); // Default google
    return engineTypeStr;
}

void TranslatorUtil::saveEngineSettings(const QString &engineName)
{
    KConfigGroup myGroup(KSharedConfig::openConfig(), groupTranslateName());
    myGroup.writeEntry(engineTranslateName(), engineName);
    myGroup.sync();
}
