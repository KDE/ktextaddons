/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogeneratetextsyntaxhighlightingmanager.h"
#include "textautogeneratetextcore_cmark_debug.h"
using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
namespace
{
bool sortCaseInsensitively(const QString &lhs, const QString &rhs)
{
    return lhs.compare(rhs, Qt::CaseInsensitive) < 0;
}
}

TextAutoGenerateTextSyntaxHighlightingManager::TextAutoGenerateTextSyntaxHighlightingManager()
{
    initialize();
    // qDebug() << " *******************************************************************: " << sizeof(TextAutoGenerateTextSyntaxHighlightingManager);
    // "88" with qobject
    // "72" without qobject
}

void TextAutoGenerateTextSyntaxHighlightingManager::initialize()
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
        qCWarning(TEXTAUTOGENERATETEXT_CORE_CMARK_LOG) << "Unable to find definition";
    }
}

KSyntaxHighlighting::Repository &TextAutoGenerateTextSyntaxHighlightingManager::repo() const
{
    return mRepo;
}

KSyntaxHighlighting::Definition TextAutoGenerateTextSyntaxHighlightingManager::def(const QString &name) const
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

KSyntaxHighlighting::Definition TextAutoGenerateTextSyntaxHighlightingManager::defaultDef() const
{
    return mDefaultDef;
}

bool TextAutoGenerateTextSyntaxHighlightingManager::syntaxHighlightingInitialized() const
{
    return mSyntaxHighlightingInitialized;
}

TextAutoGenerateTextSyntaxHighlightingManager *TextAutoGenerateTextSyntaxHighlightingManager::self()
{
    static TextAutoGenerateTextSyntaxHighlightingManager s_self;
    return &s_self;
}
