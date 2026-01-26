/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamacommonmodelavailablewidget.h"
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
OllamaCommonModelAvailableWidget::OllamaCommonModelAvailableWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainlayout"_s);
    mainLayout->setContentsMargins({});
    mainLayout->setSpacing(0);
}

OllamaCommonModelAvailableWidget::~OllamaCommonModelAvailableWidget() = default;
#include "moc_ollamacommonmodelavailablewidget.cpp"
