/*
   SPDX-FileCopyrightText: 2013-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "richtexteditfindbar.h"
#include "widgets/findutils.h"
#include "widgets/textfindreplacewidget.h"

#include <KLocalizedString>
#include <TextUtils/ConvertText>

#include <QLineEdit>
#include <QRegularExpression>
#include <QTextEdit>

using namespace TextCustomEditor;
class Q_DECL_HIDDEN TextCustomEditor::RichTextEditFindBarPrivate
{
public:
    explicit RichTextEditFindBarPrivate(QTextEdit *view)
        : mView(view)
    {
    }

    QTextEdit *const mView;
};

RichTextEditFindBar::RichTextEditFindBar(QTextEdit *view, QWidget *parent)
    : TextEditFindBarBase(parent)
    , d(new TextCustomEditor::RichTextEditFindBarPrivate(view))
{
}

RichTextEditFindBar::~RichTextEditFindBar() = default;

void RichTextEditFindBar::slotSearchText(bool backward, bool isAutoSearch)
{
    d->mView->moveCursor(QTextCursor::Start);
    searchText(backward, isAutoSearch);
}

bool RichTextEditFindBar::viewIsReadOnly() const
{
    return d->mView->isReadOnly();
}

bool RichTextEditFindBar::documentIsEmpty() const
{
    return d->mView->document()->isEmpty();
}

bool RichTextEditFindBar::searchInDocument(const QString &text, TextEditFindBarBase::FindFlags searchOptions)
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

bool RichTextEditFindBar::searchInDocument(const QRegularExpression &regExp, TextEditFindBarBase::FindFlags searchOptions)
{
    const bool found = d->mView->find(regExp, FindUtils::convertTextEditFindFlags(searchOptions));
    mFindWidget->setFoundMatch(found);
    return found;
}

void RichTextEditFindBar::autoSearchMoveCursor()
{
    QTextCursor cursor = d->mView->textCursor();
    cursor.setPosition(cursor.selectionStart());
    d->mView->setTextCursor(cursor);
}

void RichTextEditFindBar::slotReplaceText()
{
    auto textCursor = d->mView->textCursor();
    if (!textCursor.hasSelection()) {
        searchText(false, false);
        return;
    }
    const QString selectedText = textCursor.selectedText();
    bool canReplace = false;
    if (mFindWidget->isRegularExpression()) {
        canReplace = selectedText.contains(mFindWidget->searchRegularExpression());
    } else {
        const TextEditFindBarBase::FindFlags searchOptions = mFindWidget->searchOptions();
        const QString searchStr = mFindWidget->searchText();
        // Compare the way the search did: it honours the case sensitivity flag.
        const Qt::CaseSensitivity caseSensitivity = (searchOptions & TextEditFindBarBase::FindCaseSensitively) ? Qt::CaseSensitive : Qt::CaseInsensitive;
        if (searchOptions & TextEditFindBarBase::FindRespectDiacritics) {
            canReplace = (QString::compare(selectedText, searchStr, caseSensitivity) == 0);
        } else {
            // The search ignored diacritics, so ignore them here too.
            canReplace = (TextUtils::ConvertText::normalize(selectedText, caseSensitivity) == TextUtils::ConvertText::normalize(searchStr, caseSensitivity));
        }
    }
    if (canReplace) {
        textCursor.insertText(mReplaceWidget->replaceLineEdit()->text());
        // search next after replace text.
        searchText(false, false);
    }
}

void RichTextEditFindBar::slotReplaceAllText()
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
