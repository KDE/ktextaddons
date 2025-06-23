/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolcombobox.h"
using namespace Qt::Literals::StringLiterals;

#include "languageinfo.h"
#include <KLocalizedString>
using namespace TextGrammarCheck;
LanguageToolComboBox::LanguageToolComboBox(QWidget *parent)
    : QComboBox(parent)
{
    fillComboBox();
}

LanguageToolComboBox::~LanguageToolComboBox() = default;

void LanguageToolComboBox::fillComboBox(const QVector<LanguageInfo> &info)
{
    clear();
    for (int i = 0; i < info.count(); ++i) {
        const LanguageInfo infoLang = info.at(i);
        addItem(infoLang.name(), infoLang.code());
    }
}

void LanguageToolComboBox::fillComboBox()
{
    addItem(i18n("Asturian"), u"ast"_s);
    addItem(i18n("English"), u"en"_s);
    addItem(i18n("English (Australian)"), u"en-AU"_s);
    addItem(i18n("English (Canadian)"), u"en-CA"_s);
    addItem(i18n("Belarusian"), u"be"_s);
    addItem(i18n("Breton"), u"br"_s);
    addItem(i18n("Catalan"), u"ca"_s);
    addItem(i18n("Chinese"), u"zh"_s);
    addItem(i18n("Danish"), u"da"_s);
    addItem(i18n("Dutch"), u"nl"_s);
    addItem(i18n("Esperanto"), u"eo"_s);
    addItem(i18n("French"), u"fr"_s);
    addItem(i18n("Galician"), u"gl"_s);
    addItem(i18n("German"), u"de"_s);
    addItem(i18n("Greek"), u"el"_s);
    addItem(i18n("Italian"), u"it"_s);
    addItem(i18n("Japanese"), u"ja"_s);
    addItem(i18n("Khmer"), u"km"_s);
    addItem(i18n("Persian"), u"fa"_s);
    addItem(i18n("Polish"), u"pl"_s);
    addItem(i18n("Portuguese"), u"pt"_s);
    addItem(i18n("Romanian"), u"ro"_s);
    addItem(i18n("Russian"), u"ru"_s);
    addItem(i18n("Slovak"), u"sk"_s);
    addItem(i18n("Slovenian"), u"sl"_s);
    addItem(i18n("Spanish"), u"es"_s);
    addItem(i18n("Swedish"), u"sv"_s);
    addItem(i18n("Tagalog"), u"tl"_s);
    addItem(i18n("Tamil"), u"ta"_s);
    addItem(i18n("Ukrainian"), u"uk-UA"_s);
}

void LanguageToolComboBox::setLanguage(const QString &str)
{
    const int pos = findData(str);
    if (pos != -1) {
        setCurrentIndex(pos);
    }
}

QString LanguageToolComboBox::language() const
{
    return currentData().toString();
}

#include "moc_languagetoolcombobox.cpp"
