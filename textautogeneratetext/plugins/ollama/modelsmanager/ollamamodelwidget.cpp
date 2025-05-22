/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelwidget.h"
#include "ollamamodelsearchwidget.h"
#include <QVBoxLayout>
OllamaModelWidget::OllamaModelWidget(QWidget *parent)
    : QWidget{parent}
    , mSearchWidget(new OllamaModelSearchWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});

    mSearchWidget->setObjectName(QStringLiteral("mSearchWidget"));
    mainLayout->addWidget(mSearchWidget);
}

OllamaModelWidget::~OllamaModelWidget() = default;

#include "moc_ollamamodelwidget.cpp"
