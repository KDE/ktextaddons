/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateaddmcpserverwidget.h"
#include <QFormLayout>

using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateAddMcpServerWidget::TextAutoGenerateAddMcpServerWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});
}

TextAutoGenerateAddMcpServerWidget::~TextAutoGenerateAddMcpServerWidget() = default;
#include "moc_textautogenerateaddmcpserverwidget.cpp"
