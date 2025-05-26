/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelwidget.h"
#include "ollamamodeldownloadprogresswidget.h"
#include "ollamamodelinfosmanager.h"
#include "ollamamodelinfosmodel.h"
#include "ollamamodelinfossortproxymodel.h"
#include "ollamamodelinfowidget.h"
#include "ollamamodellistview.h"
#include "ollamamodelsearchwidget.h"
#include <QSplitter>
#include <QStackedWidget>
#include <QVBoxLayout>

OllamaModelWidget::OllamaModelWidget(QWidget *parent)
    : QWidget{parent}
    , mSearchWidget(new OllamaModelSearchWidget(this))
    , mListView(new OllamaModelListView(this))
    , mInfoWidget(new OllamaModelInfoWidget(this))
    , mProxyModel(new OllamaModelInfosSortProxyModel(this))
    , mOllamaModelDownloadProgressWidget(new OllamaModelDownloadProgressWidget(this))
    , mStackedWidget(new QStackedWidget(this))
{
    auto splitter = new QSplitter(this);
    splitter->setOrientation(Qt::Horizontal);
    splitter->setObjectName(QStringLiteral("splitter"));
    splitter->setChildrenCollapsible(false);
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});

    mSearchWidget->setObjectName(QStringLiteral("mSearchWidget"));
    mainLayout->addWidget(mSearchWidget);
    mainLayout->addWidget(splitter, 1);

    mListView->setObjectName(QStringLiteral("mListView"));
    splitter->addWidget(mListView);

    mInfoWidget->setObjectName(QStringLiteral("mInfoWidget"));
    splitter->addWidget(mStackedWidget);
    mStackedWidget->hide();

    mOllamaModelDownloadProgressWidget->setObjectName(QStringLiteral("mOllamaModelDownloadProgressWidget"));
    mStackedWidget->setObjectName(QStringLiteral("mStackedWidget"));
    mStackedWidget->addWidget(mInfoWidget);
    mStackedWidget->addWidget(mOllamaModelDownloadProgressWidget);
    mStackedWidget->setCurrentWidget(mInfoWidget);
    connect(mInfoWidget, &OllamaModelInfoWidget::downloadModel, this, &OllamaModelWidget::slotDownloadModel);

    auto model = new OllamaModelInfosModel(this);
    mProxyModel->setSourceModel(model);
    OllamaModelInfosManager manager;
    if (manager.loadAvailableModels()) {
        model->setModelInfos(manager.modelInfos());
    }
    mListView->setModel(mProxyModel);
    connect(mSearchWidget, &OllamaModelSearchWidget::searchText, mProxyModel, &OllamaModelInfosSortProxyModel::setFilterFixedString);
    connect(mSearchWidget, &OllamaModelSearchWidget::categoriesChanged, mProxyModel, &OllamaModelInfosSortProxyModel::setCategories);
    connect(mListView, &OllamaModelListView::clicked, this, &OllamaModelWidget::slotClicked);
}

OllamaModelWidget::~OllamaModelWidget() = default;

void OllamaModelWidget::slotClicked(const QModelIndex &index)
{
    if (!index.isValid()) {
        return;
    }
    mStackedWidget->setVisible(true);
    mStackedWidget->setCurrentWidget(mInfoWidget);
    mInfoWidget->generateWidget(index);
}

void OllamaModelWidget::slotDownloadModel(const QString &url)
{
    qDebug() << " url " << url;
    // TODO use url
    mStackedWidget->setCurrentWidget(mOllamaModelDownloadProgressWidget);
}

#include "moc_ollamamodelwidget.cpp"
