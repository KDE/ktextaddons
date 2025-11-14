/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogeneratejsonplaintexteditwidget.h"
#include "textautogeneratetextwidget_debug.h"
#include <KSyntaxHighlighting/Definition>
#include <KSyntaxHighlighting/SyntaxHighlighter>
#include <KSyntaxHighlighting/Theme>
#include <QVBoxLayout>
#include <TextCustomEditor/PlainTextEditor>
#include <TextCustomEditor/PlainTextEditorWidget>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateJsonPlainTextEditor::TextAutoGenerateJsonPlainTextEditor(QWidget *parent)
    : TextCustomEditor::PlainTextEditor(parent)
{
    setReadOnly(true);
    setSearchSupport(true);
}

TextAutoGenerateJsonPlainTextEditor::~TextAutoGenerateJsonPlainTextEditor() = default;

TextAutoGenerateJsonPlainTextEditWidget::TextAutoGenerateJsonPlainTextEditWidget(QWidget *parent)
    : QWidget{parent}
    , mPlainTextEdit(new TextCustomEditor::PlainTextEditorWidget(new TextAutoGenerateJsonPlainTextEditor(parent), this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mPlainTextEdit->setObjectName(u"mPlainTextEdit"_s);
    mPlainTextEdit->setReadOnly(true);
    mainLayout->addWidget(mPlainTextEdit);

    const KSyntaxHighlighting::Definition def = mRepo.definitionForName(u"Json"_s);
    if (!def.isValid()) {
        qCWarning(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "Invalid definition name";
    }

    auto hl = new KSyntaxHighlighting::SyntaxHighlighter(mPlainTextEdit->editor()->document());
    hl->setTheme((palette().color(QPalette::Base).lightness() < 128) ? mRepo.defaultTheme(KSyntaxHighlighting::Repository::DarkTheme)
                                                                     : mRepo.defaultTheme(KSyntaxHighlighting::Repository::LightTheme));
    hl->setDefinition(def);
}

TextAutoGenerateJsonPlainTextEditWidget::~TextAutoGenerateJsonPlainTextEditWidget() = default;

void TextAutoGenerateJsonPlainTextEditWidget::setPlainText(const QString &str)
{
    mPlainTextEdit->setPlainText(str);
}

#include "moc_textautogeneratejsonplaintexteditwidget.cpp"
