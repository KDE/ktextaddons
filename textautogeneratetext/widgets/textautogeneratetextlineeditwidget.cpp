/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextlineeditwidget.h"
#include "widgets/textautogenerateresultwidget.h"
#include "widgets/textautogeneratetextlineedit.h"
#include <QHBoxLayout>

using namespace TextAutogenerateText;
TextAutogenerateTextLineEditWidget::TextAutogenerateTextLineEditWidget(QWidget *parent)
    : QWidget{parent}
    , mTextAutogenerateResultWidget(new TextAutogenerateResultWidget(this))
    , mTextAutogenerateTextLineEdit(new TextAutogenerateTextLineEdit(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(QMargins{});

    mTextAutogenerateResultWidget->setObjectName(QStringLiteral("mTextAutogenerateResultWidget"));
    mainLayout->addWidget(mTextAutogenerateResultWidget);

    mTextAutogenerateTextLineEdit->setObjectName(QStringLiteral("mTextAutogenerateTextLineEdit"));
    mainLayout->addWidget(mTextAutogenerateTextLineEdit);
    // TODO
}

TextAutogenerateTextLineEditWidget::~TextAutogenerateTextLineEditWidget() = default;

#include "moc_textautogeneratetextlineeditwidget.cpp"
