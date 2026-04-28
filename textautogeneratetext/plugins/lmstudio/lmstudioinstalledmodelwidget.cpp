/*
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "lmstudioinstalledmodelwidget.h"
#include "modelsmanager/lmstudiomodelinstalledwidget.h"
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
LMStudioInstalledModelWidget::LMStudioInstalledModelWidget(LMStudioManager *manager, QWidget *parent)
    : QWidget{parent}
    , mLMStudioModelInstalledWidget(new LMStudioModelInstalledWidget(manager, this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);
    mainLayout->setContentsMargins({});

    mLMStudioModelInstalledWidget->setObjectName(u"mLMStudioModelInstalledWidget"_s);
    mainLayout->addWidget(mLMStudioModelInstalledWidget);
}

LMStudioInstalledModelWidget::~LMStudioInstalledModelWidget() = default;

#include "moc_lmstudioinstalledmodelwidget.cpp"
