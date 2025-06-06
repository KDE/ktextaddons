/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "richtexteditorwidget.h"
#include "richtexteditfindbar.h"
#include "richtexteditor.h"

#include "config-textcustomeditor.h"
#include <QTextCursor>
#include <QVBoxLayout>
#if HAVE_KTEXTADDONS_TEXT_TO_SPEECH_SUPPORT
#include <TextEditTextToSpeech/TextToSpeechContainerWidget>
#endif
#include <TextAddonsWidgets/SlideContainer>

using namespace TextCustomEditor;

class Q_DECL_HIDDEN TextCustomEditor::RichTextEditorWidgetPrivate
{
public:
    RichTextEditorWidgetPrivate() = default;

    TextCustomEditor::RichTextEditFindBar *mFindBar = nullptr;
    RichTextEditor *mEditor = nullptr;
#if HAVE_KTEXTADDONS_TEXT_TO_SPEECH_SUPPORT
    TextEditTextToSpeech::TextToSpeechContainerWidget *mTextToSpeechWidget = nullptr;
#endif
    TextAddonsWidgets::SlideContainer *mSliderContainer = nullptr;
};

RichTextEditorWidget::RichTextEditorWidget(RichTextEditor *customEditor, QWidget *parent)
    : QWidget(parent)
    , d(new TextCustomEditor::RichTextEditorWidgetPrivate)
{
    init(customEditor);
}

RichTextEditorWidget::RichTextEditorWidget(QWidget *parent)
    : QWidget(parent)
    , d(new TextCustomEditor::RichTextEditorWidgetPrivate)
{
    init();
}

RichTextEditorWidget::~RichTextEditorWidget() = default;

void RichTextEditorWidget::clear()
{
    d->mEditor->clear();
}

RichTextEditor *RichTextEditorWidget::editor() const
{
    return d->mEditor;
}

void RichTextEditorWidget::setAcceptRichText(bool b)
{
    d->mEditor->setAcceptRichText(b);
}

bool RichTextEditorWidget::acceptRichText() const
{
    return d->mEditor->acceptRichText();
}

void RichTextEditorWidget::setSpellCheckingConfigFileName(const QString &_fileName)
{
    d->mEditor->setSpellCheckingConfigFileName(_fileName);
}

void RichTextEditorWidget::setHtml(const QString &html)
{
    d->mEditor->setHtml(html);
}

QString RichTextEditorWidget::toHtml() const
{
    return d->mEditor->toHtml();
}

void RichTextEditorWidget::setPlainText(const QString &text)
{
    d->mEditor->setPlainText(text);
}

bool RichTextEditorWidget::isEmpty() const
{
    return d->mEditor->document()->isEmpty();
}

QString RichTextEditorWidget::toPlainText() const
{
    return d->mEditor->toPlainText();
}

void RichTextEditorWidget::init(RichTextEditor *customEditor)
{
    auto lay = new QVBoxLayout(this);
    lay->setContentsMargins({});
#if HAVE_KTEXTADDONS_TEXT_TO_SPEECH_SUPPORT
    d->mTextToSpeechWidget = new TextEditTextToSpeech::TextToSpeechContainerWidget(this);
    lay->addWidget(d->mTextToSpeechWidget);
#endif
    if (customEditor) {
        d->mEditor = customEditor;
    } else {
        d->mEditor = new RichTextEditor;
    }
#if HAVE_KTEXTADDONS_TEXT_TO_SPEECH_SUPPORT
    connect(d->mEditor, &RichTextEditor::say, d->mTextToSpeechWidget, &TextEditTextToSpeech::TextToSpeechContainerWidget::say);
#endif
    lay->addWidget(d->mEditor);

    d->mSliderContainer = new TextAddonsWidgets::SlideContainer(this);

    d->mFindBar = new TextCustomEditor::RichTextEditFindBar(d->mEditor, this);
    d->mFindBar->setHideWhenClose(false);
    connect(d->mFindBar, &TextCustomEditor::RichTextEditFindBar::displayMessageIndicator, d->mEditor, &RichTextEditor::slotDisplayMessageIndicator);

    connect(d->mFindBar, &TextCustomEditor::RichTextEditFindBar::hideFindBar, this, &RichTextEditorWidget::slotHideFindBar);
    d->mSliderContainer->setContent(d->mFindBar);
    lay->addWidget(d->mSliderContainer);

    connect(d->mEditor, &RichTextEditor::findText, this, &RichTextEditorWidget::slotFind);
    connect(d->mEditor, &RichTextEditor::replaceText, this, &RichTextEditorWidget::slotReplace);
}

void RichTextEditorWidget::slotHideFindBar()
{
    d->mSliderContainer->slideOut();
    d->mEditor->setFocus();
}

bool RichTextEditorWidget::isReadOnly() const
{
    return d->mEditor->isReadOnly();
}

void RichTextEditorWidget::setReadOnly(bool readOnly)
{
    d->mEditor->setReadOnly(readOnly);
}

void RichTextEditorWidget::slotReplace()
{
    if (d->mEditor->searchSupport()) {
        if (d->mEditor->textCursor().hasSelection()) {
            d->mFindBar->setText(d->mEditor->textCursor().selectedText());
        }
        d->mFindBar->showReplace();
        d->mSliderContainer->slideIn();
        d->mFindBar->focusAndSetCursor();
    }
}

void RichTextEditorWidget::slotFindNext()
{
    if (d->mEditor->searchSupport()) {
        if (d->mFindBar->isVisible()) {
            d->mFindBar->findNext();
        } else {
            slotFind();
        }
    }
}

void RichTextEditorWidget::slotFind()
{
    if (d->mEditor->searchSupport()) {
        if (d->mEditor->textCursor().hasSelection()) {
            d->mFindBar->setText(d->mEditor->textCursor().selectedText());
        }
        d->mEditor->moveCursor(QTextCursor::Start);

        d->mFindBar->showFind();
        d->mSliderContainer->slideIn();
        d->mFindBar->focusAndSetCursor();
    }
}

#include "moc_richtexteditorwidget.cpp"
