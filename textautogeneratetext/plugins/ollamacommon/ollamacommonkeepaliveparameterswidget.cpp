/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamacommonkeepaliveparameterswidget.h"
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
OllamaCommonKeepAliveParametersWidget::OllamaCommonKeepAliveParametersWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainlayout"_s);
    mainLayout->setContentsMargins({});
}

OllamaCommonKeepAliveParametersWidget::~OllamaCommonKeepAliveParametersWidget() = default;

#include "moc_ollamacommonkeepaliveparameterswidget.cpp"
