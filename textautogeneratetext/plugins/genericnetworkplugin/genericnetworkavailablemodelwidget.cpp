/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkavailablemodelwidget.h"
#include "genericnetworkmanager.h"
#include "modelsmanager/genericnetworkmodelavailablewidget.h"
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
GenericNetworkAvailableModelWidget::GenericNetworkAvailableModelWidget(GenericNetworkManager *manager, QWidget *parent)
    : QWidget{parent}
    , mGenericNetworkModelAvailableWidget(new GenericNetworkModelAvailableWidget(manager, this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);
    mainLayout->setContentsMargins({});

    mGenericNetworkModelAvailableWidget->setObjectName(u"mGenericNetworkModelAvailableWidget"_s);
    mainLayout->addWidget(mGenericNetworkModelAvailableWidget);
}

GenericNetworkAvailableModelWidget::~GenericNetworkAvailableModelWidget() = default;

#include "moc_genericnetworkavailablemodelwidget.cpp"
