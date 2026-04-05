/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "mainwidget.h"
#include <QSplitter>
#include <QVBoxLayout>

MainWidget::MainWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QVBoxLayout(this);
    auto splitter = new QSplitter(this);
    mainLayout->addWidget(splitter);
    splitter->setChildrenCollapsible(false);
    // TODO
}

MainWidget::~MainWidget() = default;

#include "moc_mainwidget.cpp"
