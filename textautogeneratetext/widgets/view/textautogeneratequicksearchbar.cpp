/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratequicksearchbar.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QToolButton>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateQuickSearchBar::TextAutoGenerateQuickSearchBar(QWidget *parent)
    : QWidget{parent}
    , mSearchLineEdit(new QLineEdit(this))
    , mNextButton(new QToolButton(this))
    , mPreviousButton(new QToolButton(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mSearchLineEdit->setObjectName(u"mSearchLineEdit"_s);
    mainLayout->addWidget(mSearchLineEdit);
    const auto shortcut = QKeySequence(Qt::CTRL | Qt::Key_K);
    mSearchLineEdit->setPlaceholderText(i18nc("@info:placeholder", "Search… (%1)", shortcut.toString(QKeySequence::NativeText)));
    KLineEditEventHandler::catchReturnKey(mSearchLineEdit);
    mSearchLineEdit->setClearButtonEnabled(true);
    connect(mSearchLineEdit, &QLineEdit::textChanged, this, [this](const QString &str) {
        const bool searchTextIsEmpty = str.isEmpty();
        mNextButton->setEnabled(!searchTextIsEmpty);
        mPreviousButton->setEnabled(!searchTextIsEmpty);
        Q_EMIT searchTextRequested(str);
    });

    mNextButton->setObjectName(u"mNextButton"_s);
    mNextButton->setAutoRaise(true);
    mNextButton->setIcon(QIcon::fromTheme(u"go-down-search"_s));
    mNextButton->setToolTip(i18nc("Find and go to the next search match", "Next"));
    mNextButton->setEnabled(false);
    mainLayout->addWidget(mNextButton);

    mPreviousButton->setObjectName(u"mPreviousButton"_s);
    mPreviousButton->setAutoRaise(true);
    mPreviousButton->setEnabled(false);
    mPreviousButton->setIcon(QIcon::fromTheme(u"go-up-search"_s));
    mPreviousButton->setToolTip(i18nc("Find and go to the previous search match", "Previous"));
    mainLayout->addWidget(mPreviousButton);
}

TextAutoGenerateQuickSearchBar::~TextAutoGenerateQuickSearchBar() = default;

void TextAutoGenerateQuickSearchBar::updateButtons(bool next, bool previous)
{
}

QString TextAutoGenerateQuickSearchBar::searchText() const
{
    return mSearchLineEdit->text();
}

void TextAutoGenerateQuickSearchBar::setTearchText(const QString &str)
{
    mSearchLineEdit->setText(str);
}

void TextAutoGenerateQuickSearchBar::findNext()
{
}

void TextAutoGenerateQuickSearchBar::findPrev()
{
}

#include "moc_textautogeneratequicksearchbar.cpp"
