/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamacommonoptionswidget.h"
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;

OllamaCommonOptionsWidget::OllamaCommonOptionsWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainlayout"_s);
    mainLayout->setContentsMargins({});
}

OllamaCommonOptionsWidget::~OllamaCommonOptionsWidget() = default;
