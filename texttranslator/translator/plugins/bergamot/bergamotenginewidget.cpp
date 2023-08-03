/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bergamotenginewidget.h"
#include <KLocalizedString>
#include <QVBoxLayout>

BergamotEngineWidget::BergamotEngineWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});
}

BergamotEngineWidget::~BergamotEngineWidget() = default;
