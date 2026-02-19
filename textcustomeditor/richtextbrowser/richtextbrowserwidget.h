/*
   SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textcustomeditor_export.h"

#include <QWidget>

namespace TextCustomEditor
{
class RichTextBrowser;
class RichTextBrowserWidgetPrivate;
/*!
 * \class TextCustomEditor::RichTextBrowserWidget
 * \inmodule TextCustomEditor
 * \inheaderfile TextCustomEditor/RichTextBrowserWidget
 *
 * \brief The RichTextBrowserWidget class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTCUSTOMEDITOR_EXPORT RichTextBrowserWidget : public QWidget
{
    Q_OBJECT
public:
    /*! Constructs a new RichTextBrowserWidget. */
    explicit RichTextBrowserWidget(QWidget *parent = nullptr);
    /*! Constructs a new RichTextBrowserWidget with a custom browser. */
    explicit RichTextBrowserWidget(RichTextBrowser *customEditor, QWidget *parent = nullptr);
    /*! Destroys the widget. */
    ~RichTextBrowserWidget() override;

    /*! Clears all content from the browser. */
    void clear();

    /*! Returns the underlying RichTextBrowser instance. */
    [[nodiscard]] RichTextBrowser *editor() const;

    /*! Sets the HTML content of the browser. */
    void setHtml(const QString &html);
    /*! Returns the HTML content of the browser. */
    [[nodiscard]] QString toHtml() const;

    /*! Sets the plain text content of the browser. */
    void setPlainText(const QString &text);
    /*! Returns the plain text content of the browser. */
    [[nodiscard]] QString toPlainText() const;

    /*! Sets whether the browser accepts rich text formatting. */
    void setAcceptRichText(bool b);
    /*! Returns whether the browser accepts rich text formatting. */
    [[nodiscard]] bool acceptRichText() const;

    /*! Returns whether the browser is empty. */
    [[nodiscard]] bool isEmpty() const;
public Q_SLOTS:
    /*! Opens the find bar to search for text. */
    void slotFindNext();
    /*! Opens the find bar to search for text. */
    void slotFind();

private:
    TEXTCUSTOMEDITOR_NO_EXPORT void slotHideFindBar();
    TEXTCUSTOMEDITOR_NO_EXPORT void init(RichTextBrowser *customEditor = nullptr);
    std::unique_ptr<RichTextBrowserWidgetPrivate> const d;
};
}
