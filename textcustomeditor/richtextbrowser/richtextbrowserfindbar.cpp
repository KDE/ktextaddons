/*
   SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "richtextbrowserfindbar.h"
#include "widgets/findutils.h"
#include "widgets/textfindreplacewidget.h"

#include <KLocalizedString>
#include <TextUtils/ConvertText>

#include <QLineEdit>
#include <QRegularExpression>
#include <QTextEdit>

using namespace TextCustomEditor;
class Q_DECL_HIDDEN TextCustomEditor::RichTextBrowserFindBarPrivate
{
public:
    RichTextBrowserFindBarPrivate(QTextEdit *view)
        : mView(view)
    {
    }

    QTextEdit *const mView;
};

RichTextBrowserFindBar::RichTextBrowserFindBar(QTextEdit *view, QWidget *parent)
    : TextEditFindBarBase(parent)
    , d(new TextCustomEditor::RichTextBrowserFindBarPrivate(view))
{
}

RichTextBrowserFindBar::~RichTextBrowserFindBar() = default;

void RichTextBrowserFindBar::slotSearchText(bool backward, bool isAutoSearch)
{
    d->mView->moveCursor(QTextCursor::Start);
    searchText(backward, isAutoSearch);
}

bool RichTextBrowserFindBar::viewIsReadOnly() const
{
    return d->mView->isReadOnly();
}

bool RichTextBrowserFindBar::documentIsEmpty() const
{
    return d->mView->document()->isEmpty();
}

bool RichTextBrowserFindBar::searchInDocument(const QString &text, TextEditFindBarBase::FindFlags searchOptions)
{
    bool found = false;
    if (searchOptions & TextEditFindBarBase::FindRespectDiacritics) {
        found = d->mView->find(text, FindUtils::convertTextEditFindFlags(searchOptions));
    } else {
        found = FindUtils::find(d->mView, text, FindUtils::convertTextEditFindFlags(searchOptions));
    }
    mFindWidget->setFoundMatch(found);
    return found;
}

bool RichTextBrowserFindBar::searchInDocument(const QRegularExpression &regExp, TextEditFindBarBase::FindFlags searchOptions)
{
    const bool found = d->mView->find(regExp, FindUtils::convertTextEditFindFlags(searchOptions));
    mFindWidget->setFoundMatch(found);
    return found;
}

void RichTextBrowserFindBar::autoSearchMoveCursor()
{
    QTextCursor cursor = d->mView->textCursor();
    cursor.setPosition(cursor.selectionStart());
    d->mView->setTextCursor(cursor);
}

void RichTextBrowserFindBar::slotReplaceText()
{
    const TextEditFindBarBase::FindFlags searchOptions = mFindWidget->searchOptions();
    if (d->mView->textCursor().hasSelection()) {
        if (mFindWidget->isRegularExpression()) {
            if (d->mView->textCursor().selectedText().contains(mFindWidget->searchRegularExpression())) {
                d->mView->textCursor().insertText(mReplaceWidget->replaceLineEdit()->text());
                // search next after replace text.
                searchText(false, false);
            }
        } else {
            if (searchOptions & TextEditFindBarBase::FindRespectDiacritics) {
                if (TextUtils::ConvertText::normalize(d->mView->textCursor().selectedText()) == TextUtils::ConvertText::normalize(mFindWidget->searchText())) {
                    d->mView->textCursor().insertText(mReplaceWidget->replaceLineEdit()->text());
                    // search next after replace text.
                    searchText(false, false);
                } else {
                    if (d->mView->textCursor().selectedText() == mFindWidget->searchText()) {
                        d->mView->textCursor().insertText(mReplaceWidget->replaceLineEdit()->text());
                        // search next after replace text.
                        searchText(false, false);
                    }
                }
            }
        }
    } else {
        searchText(false, false);
    }
}

void RichTextBrowserFindBar::slotReplaceAllText()
{
    int count = 0;
    const QString replaceStr{mReplaceWidget->replaceLineEdit()->text()};
    const TextEditFindBarBase::FindFlags searchOptions{mFindWidget->searchOptions()};
    if (mFindWidget->isRegularExpression()) {
        count = FindUtils::replaceAll(d->mView->document(), mFindWidget->searchRegularExpression(), replaceStr, searchOptions);
    } else {
        count = FindUtils::replaceAll(d->mView, mFindWidget->searchText(), replaceStr, searchOptions);
    }
    Q_EMIT displayMessageIndicator(i18np("%1 replacement made", "%1 replacements made", count));
}

#include "moc_richtexteditfindbar.cpp"
