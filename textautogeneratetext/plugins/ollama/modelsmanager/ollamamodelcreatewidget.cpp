/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelcreatewidget.h"
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStackedWidget>

OllamaModelCreateWidget::OllamaModelCreateWidget(OllamaManager *manager, QWidget *parent)
    : QWidget{parent}
    , mManager(manager)
    , mStackWidget(new QStackedWidget(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});

    mStackWidget->setObjectName(QStringLiteral("mStackWidget"));
    mainLayout->addWidget(mStackWidget);

    auto importModelFromGGUFFileButton = new QPushButton(i18nc("@action:button", "Load GGUF File…"), this);
    importModelFromGGUFFileButton->setObjectName(QStringLiteral("importModelFromGGUFFileButton"));
    mainLayout->addWidget(importModelFromGGUFFileButton);

    auto createModelButton = new QPushButton(i18nc("@action:button", "Create Model"), this);
    createModelButton->setObjectName(QStringLiteral("createModelButton"));
    mainLayout->addWidget(createModelButton);
}

OllamaModelCreateWidget::~OllamaModelCreateWidget() = default;

#include "moc_ollamamodelcreatewidget.cpp"
