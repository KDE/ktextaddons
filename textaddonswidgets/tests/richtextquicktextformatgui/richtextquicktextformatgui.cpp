/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "richtextquicktextformatgui.h"
#include "richtextquicktextformat.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QStandardPaths>
#include <QTextEdit>
using namespace Qt::Literals::StringLiterals;
RichTextQuickTextFormatGui::RichTextQuickTextFormatGui(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});
    auto textEdit = new QTextEdit(this);
    auto quickTextFormatMessage = new TextAddonsWidgets::RichTextQuickTextFormat(textEdit, this);
    connect(quickTextFormatMessage,
            &TextAddonsWidgets::RichTextQuickTextFormat::quickTextFormatRequested,
            this,
            [textEdit](TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType type) {
                switch (type) {
                case TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::Bold: {
                    QTextCharFormat format;
                    format.setFontWeight(textEdit->fontWeight() == QFont::Bold ? QFont::Normal : QFont::Bold);
                    textEdit->textCursor().mergeCharFormat(format);
                    break;
                }
                case TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::Italic: {
                    QTextCharFormat format;
                    format.setFontItalic(!textEdit->fontItalic());
                    textEdit->textCursor().mergeCharFormat(format);
                    break;
                }
                case TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::StrikeThrough:
                    // TODO
                    break;
                case TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::CodeBlock:
                    // TODO
                    break;
                case TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::BlockQuote:
                    // TODO
                    break;
                case TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType::InsertLink:
                    // TODO
                    break;
                }
            });
    mainLayout->addWidget(textEdit);
}

RichTextQuickTextFormatGui::~RichTextQuickTextFormatGui() = default;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QStandardPaths::setTestModeEnabled(true);

    RichTextQuickTextFormatGui w;
    w.show();
    return app.exec();
}

#include "moc_richtextquicktextformatgui.cpp"
