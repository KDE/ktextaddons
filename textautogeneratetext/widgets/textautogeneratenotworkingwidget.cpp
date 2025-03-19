/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratenotworkingwidget.h"
#include <QLabel>
#include <QVBoxLayout>

using namespace TextAutogenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutogenerateNotWorkingWidget::TextAutogenerateNotWorkingWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);
    mainLayout->setContentsMargins({});
    // TODO add button for configure it ?
    // TODO add message info
}

TextAutogenerateNotWorkingWidget::~TextAutogenerateNotWorkingWidget() = default;

#include "moc_textautogeneratenotworkingwidget.cpp"
