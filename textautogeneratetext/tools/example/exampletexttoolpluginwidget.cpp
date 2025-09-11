/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "exampletexttoolpluginwidget.h"
#include <QVBoxLayout>
#include <TextAutoGenerateText/TextAutoGenerateToolPluginConfigureWidget>
using namespace Qt::Literals::StringLiterals;
ExampleTextToolPluginWidget::ExampleTextToolPluginWidget(QWidget *parent)
    : QWidget{parent}
    , mConfigureWidget(new TextAutoGenerateText::TextAutoGenerateToolPluginConfigureWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mConfigureWidget->setObjectName(u"mConfigureWidget"_s);
    mainLayout->addWidget(mConfigureWidget);
}

ExampleTextToolPluginWidget::~ExampleTextToolPluginWidget() = default;

#include "moc_exampletexttoolpluginwidget.cpp"
