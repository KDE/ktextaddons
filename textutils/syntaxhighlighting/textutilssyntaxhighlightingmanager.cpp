/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textutilssyntaxhighlightingmanager.h"
#include "textutils_syntaxhighlighting_debug.h"
using namespace TextUtils;
using namespace Qt::Literals::StringLiterals;
namespace
{
bool sortCaseInsensitively(const QString &lhs, const QString &rhs)
{
    return lhs.compare(rhs, Qt::CaseInsensitive) < 0;
}
}

TextUtilsSyntaxHighlightingManager::TextUtilsSyntaxHighlightingManager()
{
    initialize();
    // qDebug() << " *******************************************************************: " << sizeof(TextUtilsSyntaxHighlightingManager);
    // "88" with qobject
    // "72" without qobject
}

void TextUtilsSyntaxHighlightingManager::initialize()
{
    mDefaultDef = mRepo.definitionForName(u"C++"_s);
    if (mDefaultDef.isValid()) {
        mSyntaxHighlightingInitialized = true;
        const auto definitions = mRepo.definitions();
        mDefinitions.reserve(definitions.size());
        for (const auto &definition : definitions) {
            mDefinitions.append(definition.name());
        }
        std::sort(mDefinitions.begin(), mDefinitions.end(), sortCaseInsensitively);
    } else {
        qCWarning(TEXTUTILS_SYNTAXHIGHLIGHTING_LOG) << "Unable to find definition";
    }
}

KSyntaxHighlighting::Repository &TextUtilsSyntaxHighlightingManager::repo() const
{
    return mRepo;
}

KSyntaxHighlighting::Definition TextUtilsSyntaxHighlightingManager::def(const QString &name) const
{
    if (name.isEmpty()) {
        return {};
    }
    auto it = std::lower_bound(mDefinitions.begin(), mDefinitions.end(), name, sortCaseInsensitively);
    if (it != mDefinitions.end() && name.compare(*it, Qt::CaseInsensitive) == 0) {
        return mRepo.definitionForName(*it);
    }
    return {};
}

KSyntaxHighlighting::Definition TextUtilsSyntaxHighlightingManager::defaultDef() const
{
    return mDefaultDef;
}

bool TextUtilsSyntaxHighlightingManager::syntaxHighlightingInitialized() const
{
    return mSyntaxHighlightingInitialized;
}

TextUtilsSyntaxHighlightingManager *TextUtilsSyntaxHighlightingManager::self()
{
    static TextUtilsSyntaxHighlightingManager s_self;
    return &s_self;
}
