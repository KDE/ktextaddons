/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextinstancemanagerwidget.h"
#include <QVBoxLayout>

using namespace TextAutoGenerateText;
TextAutoGenerateTextInstanceManagerWidget::TextAutoGenerateTextInstanceManagerWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(QMargins{});
}

TextAutoGenerateTextInstanceManagerWidget::~TextAutoGenerateTextInstanceManagerWidget() = default;

#include "moc_textautogeneratetextinstancemanagerwidget.cpp"
