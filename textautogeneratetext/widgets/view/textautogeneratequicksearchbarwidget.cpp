/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratequicksearchbarwidget.h"
#include "textautogeneratequicksearchbar.h"
#include <QKeyEvent>
#include <QVBoxLayout>
#include <TextAddonsWidgets/SlideContainer>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateQuickSearchBarWidget::TextAutoGenerateQuickSearchBarWidget(QWidget *parent)
    : QWidget{parent}
    , mSliderContainer(new TextAddonsWidgets::SlideContainer(this))
    , mQuickSearchBar(new TextAutoGenerateQuickSearchBar(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins(QMargins{});

    mSliderContainer->setObjectName(u"mSliderContainer"_s);
    mainLayout->addWidget(mSliderContainer);

    mQuickSearchBar->setObjectName(u"mQuickSearchBar"_s);
    mainLayout->addWidget(mQuickSearchBar);

    mSliderContainer->setContent(mQuickSearchBar);

    connect(mQuickSearchBar, &TextAutoGenerateQuickSearchBar::searchTextRequested, this, &TextAutoGenerateQuickSearchBarWidget::searchTextRequested);
}

TextAutoGenerateQuickSearchBarWidget::~TextAutoGenerateQuickSearchBarWidget() = default;

void TextAutoGenerateQuickSearchBarWidget::slideIn()
{
    mSliderContainer->slideIn();
}

void TextAutoGenerateQuickSearchBarWidget::slideOut()
{
    mSliderContainer->slideOut();
}

void TextAutoGenerateQuickSearchBarWidget::closeBar()
{
    // Make sure that all old searches are cleared
    mQuickSearchBar->setTearchText({});
    slideOut();
}

bool TextAutoGenerateQuickSearchBarWidget::event(QEvent *e)
{
    // Close the bar when pressing Escape.
    // Not using a QShortcut for this because it could conflict with
    // window-global actions (e.g. Emil Sedgh binds Esc to "close tab").
    // With a shortcut override we can catch this before it gets to kactions.
    const bool shortCutOverride = (e->type() == QEvent::ShortcutOverride);
    if (shortCutOverride || e->type() == QEvent::KeyPress) {
        auto kev = static_cast<QKeyEvent *>(e);
        if (kev->key() == Qt::Key_Escape) {
            if (shortCutOverride) {
                e->accept();
                return true;
            }
            e->accept();
            closeBar();
            return true;
        } else if (kev->key() == Qt::Key_Enter || kev->key() == Qt::Key_Return) {
            e->accept();
            if (shortCutOverride) {
                return true;
            }
            if (mQuickSearchBar->searchText().isEmpty()) {
                return true;
            }
#if 0
            if (kev->modifiers() & Qt::ShiftModifier) {
                findPrev();
            } else if (kev->modifiers() == Qt::NoModifier) {
                findNext();
            }
#endif
            return true;
        }
    }
    return QWidget::event(e);
}

#include "moc_textautogeneratequicksearchbarwidget.cpp"
