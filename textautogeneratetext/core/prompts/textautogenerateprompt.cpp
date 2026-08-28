/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateprompt.h"
#include <KConfigGroup>
#include <QDebug>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGeneratePrompt::TextAutoGeneratePrompt()
    : mIdentifier(QUuid::createUuid().toByteArray(QUuid::Id128))
{
}

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

QByteArray TextAutoGeneratePrompt::identifier() const
{
    return mIdentifier;
}

void TextAutoGeneratePrompt::setIdentifier(const QByteArray &newIdentifier)
{
    mIdentifier = newIdentifier;
}

bool TextAutoGeneratePrompt::isValid() const
{
    // TODO add more
    return !mIdentifier.isEmpty() && !mName.isEmpty();
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

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGeneratePrompt &t)
{
    d.space() << "name:" << t.name();
    d.space() << "text" << t.text();
    d.space() << "description:" << t.description();
    d.space() << "enabled:" << t.enabled();
    d.space() << "category:" << t.category();
    d.space() << "identifier:" << t.identifier();
    d.space() << "command:" << t.commandCompletion();
    return d;
}

void TextAutoGeneratePrompt::save(KConfigGroup &grp)
{
    grp.writeEntry("name", name());
    grp.writeEntry("text", text());
    grp.writeEntry("command", commandCompletion());
    grp.writeEntry("description", description());
    grp.writeEntry("enabled", enabled());
    grp.writeEntry("category", TextAutoGeneratePrompt::convertCategoryToString(category()));
    grp.writeEntry("identifier", identifier());
}

void TextAutoGeneratePrompt::load(const KConfigGroup &grp)
{
    setText(grp.readEntry("text"));
    setName(grp.readEntry("name"));
    setDescription(grp.readEntry("description"));
    setEnabled(grp.readEntry("enabled", true));
    setIdentifier(grp.readEntry("identifier").toLatin1());
    setCommandCompletion(grp.readEntry("command"));
    setCategory(TextAutoGeneratePrompt::convertStringToCategory(grp.readEntry("category")));
}

QString TextAutoGeneratePrompt::commandCompletion() const
{
    return mCommandCompletion;
}

void TextAutoGeneratePrompt::setCommandCompletion(const QString &newCommandCompletion)
{
    mCommandCompletion = newCommandCompletion;
}

#include "moc_textautogenerateprompt.cpp"
