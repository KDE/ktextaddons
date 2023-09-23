/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "richtextbrowserwidget.h"
#include "richtextbrowser.h"
#include "richtextbrowserfindbar.h"

#include "config-textcustomeditor.h"
#include <QTextCursor>
#include <QVBoxLayout>
#if HAVE_KTEXTADDONS_TEXT_TO_SPEECH_SUPPORT
#include <TextEditTextToSpeech/TextToSpeechContainerWidget>
#endif
#include <TextAddonsWidgets/SlideContainer>

using namespace TextCustomEditor;

class Q_DECL_HIDDEN TextCustomEditor::RichTextBrowserWidgetPrivate
{
public:
    RichTextBrowserWidgetPrivate() = default;

    TextCustomEditor::RichTextBrowserFindBar *mFindBar = nullptr;
    RichTextBrowser *mEditor = nullptr;
#if HAVE_KTEXTADDONS_TEXT_TO_SPEECH_SUPPORT
    TextEditTextToSpeech::TextToSpeechContainerWidget *mTextToSpeechWidget = nullptr;
#endif
    TextAddonsWidgets::SlideContainer *mSliderContainer = nullptr;
};

RichTextBrowserWidget::RichTextBrowserWidget(RichTextBrowser *customEditor, QWidget *parent)
    : QWidget(parent)
    , d(new TextCustomEditor::RichTextBrowserWidgetPrivate)
{
    init(customEditor);
}

RichTextBrowserWidget::RichTextBrowserWidget(QWidget *parent)
    : QWidget(parent)
    , d(new TextCustomEditor::RichTextBrowserWidgetPrivate)
{
    init();
}

RichTextBrowserWidget::~RichTextBrowserWidget() = default;

void RichTextBrowserWidget::clear()
{
    d->mEditor->clear();
}

RichTextBrowser *RichTextBrowserWidget::editor() const
{
    return d->mEditor;
}

void RichTextBrowserWidget::setAcceptRichText(bool b)
{
    d->mEditor->setAcceptRichText(b);
}

bool RichTextBrowserWidget::acceptRichText() const
{
    return d->mEditor->acceptRichText();
}

void RichTextBrowserWidget::setHtml(const QString &html)
{
    d->mEditor->setHtml(html);
}

QString RichTextBrowserWidget::toHtml() const
{
    return d->mEditor->toHtml();
}

void RichTextBrowserWidget::setPlainText(const QString &text)
{
    d->mEditor->setPlainText(text);
}

bool RichTextBrowserWidget::isEmpty() const
{
    return d->mEditor->document()->isEmpty();
}

QString RichTextBrowserWidget::toPlainText() const
{
    return d->mEditor->toPlainText();
}

void RichTextBrowserWidget::init(RichTextBrowser *customEditor)
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
        d->mEditor = new RichTextBrowser;
    }
#if HAVE_KTEXTADDONS_TEXT_TO_SPEECH_SUPPORT
    connect(d->mEditor, &RichTextBrowser::say, d->mTextToSpeechWidget, &TextEditTextToSpeech::TextToSpeechContainerWidget::say);
#endif
    lay->addWidget(d->mEditor);

    d->mSliderContainer = new TextAddonsWidgets::SlideContainer(this);

    d->mFindBar = new TextCustomEditor::RichTextBrowserFindBar(d->mEditor, this);
    d->mFindBar->setHideWhenClose(false);
    connect(d->mFindBar, &TextCustomEditor::RichTextBrowserFindBar::displayMessageIndicator, d->mEditor, &RichTextBrowser::slotDisplayMessageIndicator);

    connect(d->mFindBar, &TextCustomEditor::RichTextBrowserFindBar::hideFindBar, this, &RichTextBrowserWidget::slotHideFindBar);
    d->mSliderContainer->setContent(d->mFindBar);
    lay->addWidget(d->mSliderContainer);

    connect(d->mEditor, &RichTextBrowser::findText, this, &RichTextBrowserWidget::slotFind);
}

void RichTextBrowserWidget::slotHideFindBar()
{
    d->mSliderContainer->slideOut();
    d->mEditor->setFocus();
}

void RichTextBrowserWidget::slotFindNext()
{
    if (d->mEditor->searchSupport()) {
        if (d->mFindBar->isVisible()) {
            d->mFindBar->findNext();
        } else {
            slotFind();
        }
    }
}

void RichTextBrowserWidget::slotFind()
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

#include "moc_richtextbrowserwidget.cpp"
