/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalectemanager.h"
using namespace Qt::Literals::StringLiterals;

#include <KConfigGroup>
#include <KSharedConfig>
#include <QStandardPaths>
namespace
{
static const char myConfigGroupName[] = "Grammalecte";
}
using namespace TextGrammarCheck;
GrammalecteManager::GrammalecteManager(QObject *parent)
    : QObject(parent)
{
    loadSettings();
}

GrammalecteManager::~GrammalecteManager() = default;

GrammalecteManager *GrammalecteManager::self()
{
    static GrammalecteManager s_self;
    return &s_self;
}

void GrammalecteManager::saveSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), QLatin1StringView(myConfigGroupName));
    grp.writeEntry(u"pythonpath"_s, mPythonPath);
    grp.writeEntry(u"grammalectepath"_s, mGrammalectePath);
    grp.writeEntry(u"options"_s, mOptions);
}

QStringList GrammalecteManager::options() const
{
    return mOptions;
}

void GrammalecteManager::setOptions(const QStringList &saveOptions)
{
    mOptions = saveOptions;
}

void GrammalecteManager::loadSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), QLatin1StringView(myConfigGroupName));
    mPythonPath = grp.readEntry(u"pythonpath"_s);
    if (mPythonPath.isEmpty()) {
        mPythonPath = QStandardPaths::findExecutable(u"python3"_s);
    }
    mGrammalectePath = grp.readEntry(u"grammalectepath"_s);
    mOptions = grp.readEntry(u"options"_s, QStringList());
}

QString GrammalecteManager::pythonPath() const
{
    return mPythonPath;
}

QString GrammalecteManager::grammalectePath() const
{
    return mGrammalectePath;
}

void GrammalecteManager::setPythonPath(const QString &pythonPath)
{
    mPythonPath = pythonPath;
}

void GrammalecteManager::setGrammalectePath(const QString &grammalectePath)
{
    mGrammalectePath = grammalectePath;
}

#include "moc_grammalectemanager.cpp"
