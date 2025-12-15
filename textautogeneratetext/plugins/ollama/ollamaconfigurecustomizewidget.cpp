/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamaconfigurecustomizewidget.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QFormLayout>
#include <QLineEdit>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
OllamaConfigureCustomizeWidget::OllamaConfigureCustomizeWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});
}

OllamaConfigureCustomizeWidget::~OllamaConfigureCustomizeWidget() = default;

#include "moc_ollamaconfigurecustomizewidget.cpp"
