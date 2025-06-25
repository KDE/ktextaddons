/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkmodelavailableinfowidget.h"
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
GenericNetworkModelAvailableInfoWidget::GenericNetworkModelAvailableInfoWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainlayout"_s);
    mainLayout->setContentsMargins({});
    mainLayout->setSpacing(0);
}

GenericNetworkModelAvailableInfoWidget::~GenericNetworkModelAvailableInfoWidget() = default;

#include "moc_genericnetworkmodelavailableinfowidget.cpp"
