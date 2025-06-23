/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolmanager.h"

#include <KConfigGroup>
#include <KSharedConfig>
#include <QColor>
#include <QNetworkAccessManager>
#include <QRandomGenerator>
using namespace Qt::Literals::StringLiterals;
namespace
{
static const char myLanguageToolManagerGroupName[] = "LanguageTool";
}
using namespace TextGrammarCheck;
LanguageToolManager::LanguageToolManager(QObject *parent)
    : QObject(parent)
    , mNetworkAccessManager(new QNetworkAccessManager(this))
{
    mNetworkAccessManager->setRedirectPolicy(QNetworkRequest::NoLessSafeRedirectPolicy);
    mNetworkAccessManager->setStrictTransportSecurityEnabled(true);
    mNetworkAccessManager->enableStrictTransportSecurityStore(true);
    loadSettings();
}

LanguageToolManager::~LanguageToolManager() = default;

LanguageToolManager *LanguageToolManager::self()
{
    static LanguageToolManager s_self;
    return &s_self;
}

QNetworkAccessManager *LanguageToolManager::networkAccessManager() const
{
    return mNetworkAccessManager;
}

QString LanguageToolManager::languageToolCheckPath() const
{
    if (mLanguageToolPath.isEmpty()) {
        return {};
    }
    return mLanguageToolPath + u"/check"_s;
}

QString LanguageToolManager::languageToolLanguagesPath() const
{
    if (mLanguageToolPath.isEmpty()) {
        return {};
    }
    return convertToLanguagePath(mLanguageToolPath);
}

QString LanguageToolManager::convertToLanguagePath(const QString &path)
{
    return path + u"/languages"_s;
}

QColor LanguageToolManager::grammarColorForError(const QString &error)
{
    QColor col = mGrammarColor.value(error);
    if (col.isValid()) {
        return col;
    }
    col.setRgb(QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256));
    // Generate color.
    mGrammarColor.insert(error, col);
    return col;
}

QString LanguageToolManager::languageToolPath() const
{
    return mLanguageToolPath;
}

void LanguageToolManager::setLanguageToolPath(const QString &path)
{
    mLanguageToolPath = path;
}

void LanguageToolManager::loadSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), QLatin1StringView(myLanguageToolManagerGroupName));
    mLanguageToolPath = grp.readEntry(u"languagetoolpath"_s, QStringLiteral("https://api.languagetoolplus.com/v2"));
    if (mLanguageToolPath == "https://languagetool.org/api/v2"_L1) {
        mLanguageToolPath = u"https://api.languagetoolplus.com/v2"_s;
    }
    mLanguage = grp.readEntry(u"language"_s, QStringLiteral("en"));
    mUseLocalInstance = grp.readEntry(u"useLocalInstance"_s, false);
    // TODO add options ?
}

void LanguageToolManager::saveSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), QLatin1StringView(myLanguageToolManagerGroupName));
    grp.writeEntry(u"languagetoolpath"_s, mLanguageToolPath);
    grp.writeEntry(u"language"_s, mLanguage);
    grp.writeEntry(u"useLocalInstance"_s, mUseLocalInstance);
}

QString LanguageToolManager::language() const
{
    return mLanguage;
}

void LanguageToolManager::setLanguage(const QString &language)
{
    mLanguage = language;
}

bool LanguageToolManager::useLocalInstance() const
{
    return mUseLocalInstance;
}

void LanguageToolManager::setUseLocalInstance(bool useLocalInstance)
{
    mUseLocalInstance = useLocalInstance;
}

bool LanguageToolManager::allowToGetListOfLanguages() const
{
    return mUseLocalInstance;
}

#include "moc_languagetoolmanager.cpp"
