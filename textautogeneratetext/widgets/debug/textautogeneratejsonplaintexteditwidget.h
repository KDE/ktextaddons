/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_private_export.h"
#include <KSyntaxHighlighting/Repository>
#include <TextCustomEditor/PlainTextEditor>
namespace TextCustomEditor
{
class PlainTextEditorWidget;
}
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateJsonPlainTextEditor : public TextCustomEditor::PlainTextEditor
{
    Q_OBJECT
public:
    explicit TextAutoGenerateJsonPlainTextEditor(QWidget *parent = nullptr);
    ~TextAutoGenerateJsonPlainTextEditor() override;
};

class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateJsonPlainTextEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateJsonPlainTextEditWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateJsonPlainTextEditWidget() override;

    void setPlainText(const QString &str);

private:
    TextCustomEditor::PlainTextEditorWidget *const mPlainTextEdit;
    KSyntaxHighlighting::Repository mRepo;
};
}
