/*
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "lmstudiomodelinstalledinfowidget.h"
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
LMStudioModelInstalledInfoWidget::LMStudioModelInstalledInfoWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainlayout"_s);
    mainLayout->setContentsMargins({});
    mainLayout->setSpacing(0);
}

LMStudioModelInstalledInfoWidget::~LMStudioModelInstalledInfoWidget() = default;

#include "moc_lmstudiomodelinstalledinfowidget.cpp"
