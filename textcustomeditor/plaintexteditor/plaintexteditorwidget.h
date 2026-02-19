/*
   SPDX-FileCopyrightText: 2013-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textcustomeditor_export.h"
#include <QWidget>

namespace TextCustomEditor
{
class PlainTextEditor;
class PlainTextEditorWidgetPrivate;
/*!
 * \class TextCustomEditor::PlainTextEditorWidget
 * \inmodule TextCustomEditor
 * \inheaderfile TextCustomEditor/PlainTextEditorWidget
 *
 * \brief The PlainTextEditorWidget class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTCUSTOMEDITOR_EXPORT PlainTextEditorWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool readOnly READ isReadOnly WRITE setReadOnly)
public:
    /*! Constructs a new PlainTextEditorWidget. */
    explicit PlainTextEditorWidget(QWidget *parent = nullptr);
    /*! Constructs a new PlainTextEditorWidget with a custom editor. */
    explicit PlainTextEditorWidget(PlainTextEditor *customEditor, QWidget *parent = nullptr);
    /*! Destroys the widget. */
    ~PlainTextEditorWidget() override;

    /*! Returns the underlying PlainTextEditor instance. */
    [[nodiscard]] PlainTextEditor *editor() const;

    /*! Sets whether the editor is read-only. */
    void setReadOnly(bool readOnly);
    /*! Returns whether the editor is read-only. */
    [[nodiscard]] bool isReadOnly() const;

    /*! Sets the plain text content of the editor. */
    void setPlainText(const QString &text);
    /*! Returns the plain text content of the editor. */
    [[nodiscard]] QString toPlainText() const;

    /*! Clears all text from the editor. */
    void clear();
    /*! Sets the configuration file name for spell checking. */
    void setSpellCheckingConfigFileName(const QString &_fileName);

    /*! Returns whether the editor is empty. */
    [[nodiscard]] bool isEmpty() const;

private:
    TEXTCUSTOMEDITOR_NO_EXPORT void slotFind();
    TEXTCUSTOMEDITOR_NO_EXPORT void slotReplace();

    TEXTCUSTOMEDITOR_NO_EXPORT void slotHideFindBar();
    TEXTCUSTOMEDITOR_NO_EXPORT void init(PlainTextEditor *customEditor = nullptr);
    std::unique_ptr<PlainTextEditorWidgetPrivate> const d;
};
}
