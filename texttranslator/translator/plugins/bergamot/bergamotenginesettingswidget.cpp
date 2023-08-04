/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "bergamotenginesettingswidget.h"
#include <QVBoxLayout>

BergamotEngineSettingsWidget::BergamotEngineSettingsWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});
}

BergamotEngineSettingsWidget::~BergamotEngineSettingsWidget() = default;

#include "moc_bergamotenginesettingswidget.cpp"
