/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "richtextbrowserfindbar.h"
#include "widgets/findutils.h"
#include "widgets/textfindreplacewidget.h"

#include <KLocalizedString>
#include <TextUtils/ConvertText>

#include <QRegularExpression>
#include <QTextBrowser>

using namespace TextCustomEditor;
class Q_DECL_HIDDEN TextCustomEditor::RichTextBrowserFindBarPrivate
{
public:
    RichTextBrowserFindBarPrivate(QTextBrowser *view)
        : mView(view)
    {
    }

    QTextBrowser *const mView;
};

RichTextBrowserFindBar::RichTextBrowserFindBar(QTextBrowser *view, QWidget *parent)
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
    return true;
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
    // Nothing as readonly
}

void RichTextBrowserFindBar::slotReplaceAllText()
{
    // Nothing as readonly
}

#include "moc_richtextbrowserfindbar.cpp"
