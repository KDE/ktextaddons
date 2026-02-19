/*
   SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textcustomeditor_export.h"
#include <TextCustomEditor/TextEditFindBarBase>

class QPlainTextEdit;
namespace TextCustomEditor
{
class PlainTextEditFindBarPrivate;
/*!
 * \class TextCustomEditor::PlainTextEditFindBar
 * \inmodule TextCustomEditor
 * \inheaderfile TextCustomEditor/PlainTextEditFindBar
 *
 * \brief The PlainTextEditFindBar class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTCUSTOMEDITOR_EXPORT PlainTextEditFindBar : public TextEditFindBarBase
{
    Q_OBJECT

public:
    /*! Constructs a find bar for a QPlainTextEdit. */
    explicit PlainTextEditFindBar(QPlainTextEdit *view, QWidget *parent = nullptr);
    /*! Destroys the find bar. */
    ~PlainTextEditFindBar() override;

protected:
    /*! Returns whether the plain text editor is read-only. */
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
    std::unique_ptr<PlainTextEditFindBarPrivate> const d;
};
}
