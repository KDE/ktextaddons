/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textutils_export.h"
#include <KSyntaxHighlighting/Definition>
#include <KSyntaxHighlighting/Repository>
namespace TextUtils
{
/*!
 * \brief The TextUtilsSyntaxHighlightingManager class
 * \author Laurent Montel <montel@kde.org>
 * \class TextUtils::TextUtilsSyntaxHighlightingManager
 * \inheaderfile TextUtils/TextUtilsSyntaxHighlightingManager
 * \inmodule TextUtils
 */
class TEXTUTILS_EXPORT TextUtilsSyntaxHighlightingManager
{
public:
    /*!
     * \brief Destructor for TextUtilsSyntaxHighlightingManager
     */
    ~TextUtilsSyntaxHighlightingManager() = default;

    /*!
     * \brief Returns the singleton instance of TextUtilsSyntaxHighlightingManager
     * \return Pointer to the singleton instance
     */
    static TextUtilsSyntaxHighlightingManager *self();

    /*!
     * \brief Checks if syntax highlighting has been initialized
     * \return True if syntax highlighting is initialized, false otherwise
     */
    [[nodiscard]] bool syntaxHighlightingInitialized() const;

    /*!
     * \brief Gets a syntax definition by name
     * \param name The name of the syntax definition
     * \return The KSyntaxHighlighting::Definition object
     */
    [[nodiscard]] KSyntaxHighlighting::Definition def(const QString &name) const;
    /*!
     * \brief Gets the default syntax definition
     * \return The default KSyntaxHighlighting::Definition object
     */
    [[nodiscard]] KSyntaxHighlighting::Definition defaultDef() const;

    /*!
     * \brief Returns the syntax highlighting repository
     * \return Reference to the KSyntaxHighlighting::Repository
     */
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
