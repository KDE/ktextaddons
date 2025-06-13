/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkavailablemodelwidget.h"
#include "genericnetworkmanager.h"
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
GenericNetworkAvailableModelWidget::GenericNetworkAvailableModelWidget(GenericNetworkManager *manager, QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);
    mainLayout->setContentsMargins({});
}

GenericNetworkAvailableModelWidget::~GenericNetworkAvailableModelWidget() = default;

#include "moc_genericnetworkavailablemodelwidget.cpp"
