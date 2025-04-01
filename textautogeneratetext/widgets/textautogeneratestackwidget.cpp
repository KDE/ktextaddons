/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogeneratestackwidget.h"
#include "textautogeneratenotworkingwidget.h"
#include "textautogeneratewidget.h"

#include <QStackedWidget>
#include <QVBoxLayout>

using namespace TextAutogenerateText;
TextAutogenerateStackWidget::TextAutogenerateStackWidget(QWidget *parent)
    : QWidget{parent}
    , mStackedWidget(new QStackedWidget(this))
    , mTextAutogenerateNotWorkingWidget(new TextAutogenerateNotWorkingWidget(this))
    , mTextAutogenerateWidget(new TextAutogenerateWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mainLayout->addWidget(mStackedWidget);
    mTextAutogenerateNotWorkingWidget->setObjectName(QStringLiteral("mTextAutogenerateNotWorkingWidget"));
    mStackedWidget->addWidget(mTextAutogenerateNotWorkingWidget);

    mTextAutogenerateWidget->setObjectName(QStringLiteral("mTextAutogenerateWidget"));
    mStackedWidget->addWidget(mTextAutogenerateWidget);
    mStackedWidget->setCurrentWidget(mTextAutogenerateWidget);
}

TextAutogenerateStackWidget::~TextAutogenerateStackWidget() = default;

void TextAutogenerateStackWidget::setBrokenEngine(bool state, const QString &errorMessage)
{
    if (state) {
        mTextAutogenerateNotWorkingWidget->setMessageError(errorMessage);
        mStackedWidget->setCurrentWidget(mTextAutogenerateNotWorkingWidget);
    } else {
        mTextAutogenerateNotWorkingWidget->clearMessage();
        mStackedWidget->setCurrentWidget(mTextAutogenerateWidget);
    }
}

#include "moc_textautogeneratestackwidget.cpp"
