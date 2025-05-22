/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinfowidget.h"
#include <QVBoxLayout>

OllamaModelInfoWidget::OllamaModelInfoWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});
}

OllamaModelInfoWidget::~OllamaModelInfoWidget() = default;

#include "moc_ollamamodelinfowidget.cpp"
