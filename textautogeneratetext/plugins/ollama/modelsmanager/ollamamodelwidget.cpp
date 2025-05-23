/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelwidget.h"
#include "ollamamodelinfosmanager.h"
#include "ollamamodelinfosmodel.h"
#include "ollamamodelinfossortproxymodel.h"
#include "ollamamodelinfowidget.h"
#include "ollamamodellistview.h"
#include "ollamamodelsearchwidget.h"
#include <QVBoxLayout>

OllamaModelWidget::OllamaModelWidget(QWidget *parent)
    : QWidget{parent}
    , mSearchWidget(new OllamaModelSearchWidget(this))
    , mListView(new OllamaModelListView(this))
    , mInfoWidget(new OllamaModelInfoWidget(this))
    , mProxyModel(new OllamaModelInfosSortProxyModel(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});

    mSearchWidget->setObjectName(QStringLiteral("mSearchWidget"));
    mainLayout->addWidget(mSearchWidget);

    auto hbox = new QHBoxLayout();
    mainLayout->addLayout(hbox);
    hbox->setContentsMargins({});
    mListView->setObjectName(QStringLiteral("mListView"));
    hbox->addWidget(mListView);

    mInfoWidget->setObjectName(QStringLiteral("mInfoWidget"));
    hbox->addWidget(mInfoWidget);
    mInfoWidget->hide();

    auto model = new OllamaModelInfosModel(this);
    mProxyModel->setSourceModel(model);
    OllamaModelInfosManager manager;
    if (manager.loadAvailableModels()) {
        model->setModelInfos(manager.modelInfos());
    }
    mListView->setModel(mProxyModel);
    connect(mSearchWidget, &OllamaModelSearchWidget::searchText, mProxyModel, &OllamaModelInfosSortProxyModel::setFilterFixedString);
    connect(mListView, &OllamaModelListView::clicked, this, &OllamaModelWidget::slotClicked);
}

OllamaModelWidget::~OllamaModelWidget() = default;

void OllamaModelWidget::slotClicked(const QModelIndex &index)
{
    if (!index.isValid()) {
        return;
    }
    mInfoWidget->setVisible(true);
    mInfoWidget->generateWidget(index);
    qDebug() << " activated" << index;
}

#include "moc_ollamamodelwidget.cpp"
