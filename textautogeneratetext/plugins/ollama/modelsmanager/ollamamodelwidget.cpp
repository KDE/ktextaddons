/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelwidget.h"
#include "ollamamodelinfosmanager.h"
#include "ollamamodelinfosmodel.h"
#include "ollamamodelinfowidget.h"
#include "ollamamodellistview.h"
#include "ollamamodelsearchwidget.h"
#include <QVBoxLayout>

OllamaModelWidget::OllamaModelWidget(QWidget *parent)
    : QWidget{parent}
    , mSearchWidget(new OllamaModelSearchWidget(this))
    , mListView(new OllamaModelListView(this))
    , mInfoWidget(new OllamaModelInfoWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});

    mSearchWidget->setObjectName(QStringLiteral("mSearchWidget"));
    mainLayout->addWidget(mSearchWidget);

    mListView->setObjectName(QStringLiteral("mListView"));
    mainLayout->addWidget(mListView);

    mInfoWidget->setObjectName(QStringLiteral("mInfoWidget"));
    mainLayout->addWidget(mInfoWidget);

    auto model = new OllamaModelInfosModel(this);
    OllamaModelInfosManager manager;
    if (manager.loadAvailableModels()) {
        model->setModelInfos(manager.modelInfos());
    }
    mListView->setModel(model);
    // TODO add proxy model
}

OllamaModelWidget::~OllamaModelWidget() = default;

#include "moc_ollamamodelwidget.cpp"
