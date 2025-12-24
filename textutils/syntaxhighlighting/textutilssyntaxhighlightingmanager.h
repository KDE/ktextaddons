/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textutils_export.h"
#include <KSyntaxHighlighting/Definition>
#include <KSyntaxHighlighting/Repository>
namespace TextUtils
{
/**
 * @brief The TextUtilsSyntaxHighlightingManager class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTUTILS_EXPORT TextUtilsSyntaxHighlightingManager
{
public:
    ~TextUtilsSyntaxHighlightingManager() = default;

    static TextUtilsSyntaxHighlightingManager *self();

    [[nodiscard]] bool syntaxHighlightingInitialized() const;

    [[nodiscard]] KSyntaxHighlighting::Definition def(const QString &name) const;
    [[nodiscard]] KSyntaxHighlighting::Definition defaultDef() const;

    KSyntaxHighlighting::Repository &repo() const;

private:
    TextUtilsSyntaxHighlightingManager();
    TEXTUTILS_NO_EXPORT void initialize();
    mutable KSyntaxHighlighting::Repository mRepo;
    KSyntaxHighlighting::Definition mDefaultDef;
    QList<QString> mDefinitions;
    bool mSyntaxHighlightingInitialized = false;
};
}
