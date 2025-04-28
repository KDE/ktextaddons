/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openaiconfigurewidget.h"
#include <QFormLayout>

OpenAIConfigureWidget::OpenAIConfigureWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});
    // TODO add key here.
    // Store key in wallet ?
}

OpenAIConfigureWidget::~OpenAIConfigureWidget() = default;

#include "moc_openaiconfigurewidget.cpp"
