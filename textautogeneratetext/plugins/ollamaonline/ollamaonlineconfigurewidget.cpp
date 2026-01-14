/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamaonlineconfigurewidget.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QFormLayout>
#include <QLineEdit>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
OllamaOnlineConfigureWidget::OllamaOnlineConfigureWidget(QWidget *parent)
    : QWidget{parent}
    , mName(new QLineEdit(this))
    , mServerUrl(new QLineEdit(this))

{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    auto formLayout = new QFormLayout;
    formLayout->setObjectName(u"mainLayout"_s);
    formLayout->setContentsMargins({});
    mainLayout->addLayout(formLayout);
}

OllamaOnlineConfigureWidget::~OllamaOnlineConfigureWidget() = default;

#include "moc_ollamaonlineconfigurewidget.cpp"
