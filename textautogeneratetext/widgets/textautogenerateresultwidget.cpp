/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateresultwidget.h"

#include <QVBoxLayout>

using namespace TextAutogenerateText;
TextAutogenerateResultWidget::TextAutogenerateResultWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(QMargins{});
}

TextAutogenerateResultWidget::~TextAutogenerateResultWidget() = default;

#include "moc_textautogenerateresultwidget.cpp"
