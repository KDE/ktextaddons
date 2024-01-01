/*
 * SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>
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
/**
 * @brief The TextEditorCompleter class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTCUSTOMEDITOR_EXPORT TextEditorCompleter : public QObject
{
    Q_OBJECT
public:
    explicit TextEditorCompleter(QTextEdit *editor, QObject *parent);
    explicit TextEditorCompleter(QPlainTextEdit *editor, QObject *parent);
    ~TextEditorCompleter() override;

    void setCompleterStringList(const QStringList &list);

    [[nodiscard]] QCompleter *completer() const;

    void completeText();

    void setExcludeOfCharacters(const QString &excludes);

private:
    TEXTCUSTOMEDITOR_NO_EXPORT void slotCompletion(const QString &text);
    class TextEditorCompleterPrivate;
    std::unique_ptr<TextEditorCompleterPrivate> const d;
};
}
