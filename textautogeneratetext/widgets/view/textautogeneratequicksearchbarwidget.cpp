/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratequicksearchbarwidget.h"
#include "textautogeneratequicksearchbar.h"
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
}

TextAutoGenerateQuickSearchBarWidget::~TextAutoGenerateQuickSearchBarWidget() = default;
