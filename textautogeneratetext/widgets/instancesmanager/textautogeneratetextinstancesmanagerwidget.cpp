/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextinstancesmanagerwidget.h"
#include "textautogeneratetextinstancesmanagerlistview.h"
#include <QVBoxLayout>

using namespace TextAutoGenerateText;
TextAutoGenerateTextInstancesManagerWidget::TextAutoGenerateTextInstancesManagerWidget(QWidget *parent)
    : QWidget{parent}
    , mInstancesManagerListView(new TextAutoGenerateTextInstancesManagerListView(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(QMargins{});

    mInstancesManagerListView->setObjectName(QStringLiteral("mInstancesManagerListView"));
    mainLayout->addWidget(mInstancesManagerListView);
}

TextAutoGenerateTextInstancesManagerWidget::~TextAutoGenerateTextInstancesManagerWidget() = default;

#include "moc_textautogeneratetextinstancesmanagerwidget.cpp"
