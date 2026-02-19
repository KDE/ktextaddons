/*
   SPDX-FileCopyrightText: 2013-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textcustomeditor_export.h"

#include <QWidget>

namespace TextCustomEditor
{
class RichTextEditor;
class RichTextEditorWidgetPrivate;
/*!
 * \class TextCustomEditor::RichTextEditorWidget
 * \inmodule TextCustomEditor
 * \inheaderfile TextCustomEditor/RichTextEditorWidget
 *
 * \brief The RichTextEditorWidget class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTCUSTOMEDITOR_EXPORT RichTextEditorWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool readOnly READ isReadOnly WRITE setReadOnly)
public:
    /*! Constructs a new RichTextEditorWidget. */
    explicit RichTextEditorWidget(QWidget *parent = nullptr);
    /*! Constructs a new RichTextEditorWidget with a custom editor. */
    explicit RichTextEditorWidget(RichTextEditor *customEditor, QWidget *parent = nullptr);
    /*! Destroys the widget. */
    ~RichTextEditorWidget() override;

    /*! Clears all text from the editor. */
    void clear();

    /*! Returns the underlying RichTextEditor instance. */
    [[nodiscard]] RichTextEditor *editor() const;

    /*! Sets whether the editor is read-only. */
    void setReadOnly(bool readOnly);
    /*! Returns whether the editor is read-only. */
    [[nodiscard]] bool isReadOnly() const;

    /*! Sets the HTML content of the editor. */
    void setHtml(const QString &html);
    /*! Returns the HTML content of the editor. */
    [[nodiscard]] QString toHtml() const;

    /*! Sets the plain text content of the editor. */
    void setPlainText(const QString &text);
    /*! Returns the plain text content of the editor. */
    [[nodiscard]] QString toPlainText() const;

    /*! Sets whether the editor accepts rich text formatting. */
    void setAcceptRichText(bool b);
    /*! Returns whether the editor accepts rich text formatting. */
    [[nodiscard]] bool acceptRichText() const;

    /*! Sets the configuration file name for spell checking. */
    void setSpellCheckingConfigFileName(const QString &_fileName);

    /*! Returns whether the editor is empty. */
    [[nodiscard]] bool isEmpty() const;
public Q_SLOTS:
    /*! Opens the find bar to search for text. */
    void slotFindNext();
    /*! Opens the find bar to search for text. */
    void slotFind();
    /*! Opens the find and replace bar. */
    void slotReplace();

private:
    TEXTCUSTOMEDITOR_NO_EXPORT void slotHideFindBar();
    TEXTCUSTOMEDITOR_NO_EXPORT void init(RichTextEditor *customEditor = nullptr);
    std::unique_ptr<RichTextEditorWidgetPrivate> const d;
};
}
