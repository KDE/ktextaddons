/*
 * SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#pragma once

#include "textcustomeditor_export.h"
#include <QObject>
#include <memory>
class QCompleter;
class QTextEdit;
class QPlainTextEdit;

namespace TextCustomEditor
{
/*!
 * \class TextCustomEditor::TextEditorCompleter
 * \inmodule TextCustomEditor
 * \inheaderfile TextCustomEditor/TextEditorCompleter
 *
 * \brief The TextEditorCompleter class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTCUSTOMEDITOR_EXPORT TextEditorCompleter : public QObject
{
    Q_OBJECT
public:
    /*! Constructs a completer for a QTextEdit widget. */
    explicit TextEditorCompleter(QTextEdit *editor, QObject *parent);
    /*! Constructs a completer for a QPlainTextEdit widget. */
    explicit TextEditorCompleter(QPlainTextEdit *editor, QObject *parent);
    /*! Destroys the text editor completer. */
    ~TextEditorCompleter() override;

    /*! Sets the list of strings to use for completion. */
    void setCompleterStringList(const QStringList &list);

    /*! Returns the QCompleter instance used for text completion. */
    [[nodiscard]] QCompleter *completer() const;

    /*! Completes the current word based on the completion list. */
    void completeText();

    /*! Sets characters that should be excluded from completion. */
    void setExcludeOfCharacters(const QString &excludes);

private:
    TEXTCUSTOMEDITOR_NO_EXPORT void slotCompletion(const QString &text);
    class TextEditorCompleterPrivate;
    std::unique_ptr<TextEditorCompleterPrivate> const d;
};
}
