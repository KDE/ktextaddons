/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textcustomeditor_export.h"

#include <KSyntaxHighlighting/SyntaxHighlighter>
#include <Sonnet/Highlighter>

namespace KSyntaxHighlighting
{
class Format;
}

namespace TextCustomEditor
{
class PlainTextEditor;
class PlainTextSyntaxSpellCheckingHighlighterPrivate;
/*!
 * \class TextCustomEditor::PlainTextSyntaxSpellCheckingHighlighter
 * \inmodule TextCustomEditor
 * \inheaderfile TextCustomEditor/PlainTextSyntaxSpellCheckingHighlighter
 *
 * \brief The PlainTextSyntaxSpellCheckingHighlighter class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTCUSTOMEDITOR_EXPORT PlainTextSyntaxSpellCheckingHighlighter : public Sonnet::Highlighter, public KSyntaxHighlighting::AbstractHighlighter
{
public:
    /*! Constructs a syntax and spell checking highlighter for plain text. */
    explicit PlainTextSyntaxSpellCheckingHighlighter(PlainTextEditor *plainText, const QColor &misspelledColor = Qt::red);
    /*! Destroys the highlighter. */
    ~PlainTextSyntaxSpellCheckingHighlighter() override;

    /*! Toggles spell highlighting on or off. */
    void toggleSpellHighlighting(bool on);

    /*! Sets the syntax definition for highlighting. */
    void setDefinition(const KSyntaxHighlighting::Definition &def) override;

    /*! Highlights a block of text. */
    void highlightBlock(const QString &text) override;

protected:
    /*! Clears misspelled word highlighting. */
    void unsetMisspelled(int start, int count) override;

    /*! Sets the color of misspelled words. */
    void setMisspelled(int start, int count) override;

    /*! Applies syntax highlighting format. */
    void applyFormat(int offset, int length, const KSyntaxHighlighting::Format &format) override;

private:
    std::unique_ptr<PlainTextSyntaxSpellCheckingHighlighterPrivate> const d;
};
}
