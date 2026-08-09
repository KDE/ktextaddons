/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateprompt.h"
#include <QDebug>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGeneratePrompt::TextAutoGeneratePrompt() = default;
TextAutoGeneratePrompt::~TextAutoGeneratePrompt() = default;

QString TextAutoGeneratePrompt::name() const
{
    return mName;
}

void TextAutoGeneratePrompt::setName(const QString &newName)
{
    mName = newName;
}

QString TextAutoGeneratePrompt::text() const
{
    return mText;
}

void TextAutoGeneratePrompt::setText(const QString &newText)
{
    mText = newText;
}

QString TextAutoGeneratePrompt::description() const
{
    return mDescription;
}

void TextAutoGeneratePrompt::setDescription(const QString &newDescription)
{
    mDescription = newDescription;
}

bool TextAutoGeneratePrompt::enabled() const
{
    return mEnabled;
}

void TextAutoGeneratePrompt::setEnabled(bool newEnabled)
{
    mEnabled = newEnabled;
}

TextAutoGeneratePrompt::Category TextAutoGeneratePrompt::category() const
{
    return mCategory;
}

void TextAutoGeneratePrompt::setCategory(Category newCategory)
{
    mCategory = newCategory;
}

QString TextAutoGeneratePrompt::convertCategoryToString(Category c)
{
    switch (c) {
    case Category::Unknown:
        return QString();
    case Category::Travel:
        return u"travel"_s;
    case Category::Code:
        return u"code"_s;
    case Category::Misc:
        return u"misc"_s;
    }
    return {};
}

TextAutoGeneratePrompt::Category TextAutoGeneratePrompt::convertStringToCategory(const QString &str)
{
    if (str.isEmpty()) {
        return Category::Unknown;
    } else if (str == "travel"_L1) {
        return Category::Travel;
    } else if (str == "code"_L1) {
        return Category::Code;
    } else if (str == "misc"_L1) {
        return Category::Misc;
    }
    return Category::Unknown;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGeneratePrompt &t)
{
    d.space() << "name:" << t.name();
    d.space() << "text" << t.text();
    d.space() << "description:" << t.description();
    d.space() << "enabled:" << t.enabled();
    d.space() << "category:" << t.category();
    return d;
}
