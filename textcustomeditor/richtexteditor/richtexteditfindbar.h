/*
   SPDX-FileCopyrightText: 2013-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textcustomeditor_export.h"
#include <TextCustomEditor/TextEditFindBarBase>

class QTextEdit;
namespace TextCustomEditor
{
class RichTextEditFindBarPrivate;
/*!
 * \class TextCustomEditor::RichTextEditFindBar
 * \inmodule TextCustomEditor
 * \inheaderfile TextCustomEditor/RichTextEditFindBar
 *
 * \brief The RichTextEditFindBar class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTCUSTOMEDITOR_EXPORT RichTextEditFindBar : public TextEditFindBarBase
{
    Q_OBJECT
public:
    /*! Constructs a find bar for a QTextEdit. */
    explicit RichTextEditFindBar(QTextEdit *view, QWidget *parent = nullptr);
    /*! Destroys the find bar. */
    ~RichTextEditFindBar() override;

protected:
    /*! Returns whether the text editor is read-only. */
    [[nodiscard]] bool viewIsReadOnly() const override;
    /*! Returns whether the document is empty. */
    [[nodiscard]] bool documentIsEmpty() const override;
    /*! Searches for text in the document. */
    [[nodiscard]] bool searchInDocument(const QString &text, TextEditFindBarBase::FindFlags searchOptions) override;
    /*! Searches for text using regex in the document. */
    [[nodiscard]] bool searchInDocument(const QRegularExpression &regExp, TextEditFindBarBase::FindFlags searchOptions) override;
    /*! Moves the cursor after an automatic search. */
    void autoSearchMoveCursor() override;

public Q_SLOTS:
    /*! Searches for text with the given options. */
    void slotSearchText(bool backward = false, bool isAutoSearch = true) override;

private Q_SLOTS:
    void slotReplaceText() override;
    void slotReplaceAllText() override;

private:
    std::unique_ptr<RichTextEditFindBarPrivate> const d;
};
}
