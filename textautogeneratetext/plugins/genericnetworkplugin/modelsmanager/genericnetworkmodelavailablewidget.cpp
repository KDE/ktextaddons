/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkmodelavailablewidget.h"
#include "modelsmanager/genericnetworkmodelavailablelistview.h"
#include <QSplitter>
#include <QVBoxLayout>

GenericNetworkModelAvailableWidget::GenericNetworkModelAvailableWidget(QWidget *parent)
    : QWidget{parent}
    , mAvailableListView(new GenericNetworkModelAvailableListView(this))
{
    auto splitter = new QSplitter(this);
    splitter->setOrientation(Qt::Horizontal);
    splitter->setObjectName(QStringLiteral("splitter"));
    splitter->setChildrenCollapsible(false);

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});
    mainLayout->setSpacing(0);

    mainLayout->addWidget(splitter);

    splitter->addWidget(mAvailableListView);
}

GenericNetworkModelAvailableWidget::~GenericNetworkModelAvailableWidget() = default;

#include "moc_genericnetworkmodelavailablewidget.cpp"
