/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogeneratestackwidget.h"

#include <QStackedWidget>
#include <QVBoxLayout>
using namespace TextAutogenerateText;
TextAutogenerateStackWidget::TextAutogenerateStackWidget(QWidget *parent)
    : QWidget{parent}
    , mStackedWidget(new QStackedWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mainLayout->addWidget(mStackedWidget);
}

TextAutogenerateStackWidget::~TextAutogenerateStackWidget() = default;

#include "moc_textautogeneratestackwidget.cpp"
