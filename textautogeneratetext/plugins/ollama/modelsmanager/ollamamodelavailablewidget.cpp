/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelavailablewidget.h"
#include "ollamamodelavailableinfosmanager.h"
#include "ollamamodelavailableinfosmodel.h"
#include "ollamamodelavailableinfossortproxymodel.h"
#include "ollamamodelavailablelistview.h"
#include "ollamamodelavailablesearchwidget.h"
#include "ollamamodeldownloadprogresswidget.h"
#include "ollamamodelinfowidget.h"
#include <QSplitter>
#include <QStackedWidget>
#include <QVBoxLayout>

OllamaModelAvailableWidget::OllamaModelAvailableWidget(OllamaManager *manager, QWidget *parent)
    : QWidget{parent}
    , mSearchWidget(new OllamaModelAvailableSearchWidget(this))
    , mListView(new OllamaModelAvailableListView(this))
    , mInfoWidget(new OllamaModelInfoWidget(manager, this))
    , mProxyModel(new OllamaModelAvailableInfosSortProxyModel(this))
    , mOllamaModelDownloadProgressWidget(new OllamaModelDownloadProgressWidget(manager, this))
    , mStackedWidget(new QStackedWidget(this))
{
    auto splitter = new QSplitter(this);
    splitter->setOrientation(Qt::Horizontal);
    splitter->setObjectName(QStringLiteral("splitter"));
    splitter->setChildrenCollapsible(false);
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});
    mainLayout->setSpacing(0);

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
    connect(mInfoWidget, &OllamaModelInfoWidget::downloadModel, this, &OllamaModelAvailableWidget::slotDownloadModel);

    auto model = new OllamaModelAvailableInfosModel(this);
    mProxyModel->setSourceModel(model);
    OllamaModelAvailableInfosManager managerModelInfosManager;
    if (managerModelInfosManager.loadAvailableModels()) {
        model->setModelInfos(managerModelInfosManager.modelInfos());
    }
    mListView->setModel(mProxyModel);
    connect(mSearchWidget, &OllamaModelAvailableSearchWidget::searchText, mProxyModel, &OllamaModelAvailableInfosSortProxyModel::setFilterFixedString);
    connect(mSearchWidget, &OllamaModelAvailableSearchWidget::categoriesChanged, mProxyModel, &OllamaModelAvailableInfosSortProxyModel::setCategories);
    connect(mListView, &OllamaModelAvailableListView::clicked, this, &OllamaModelAvailableWidget::slotClicked);
    connect(mSearchWidget, &OllamaModelAvailableSearchWidget::removeModel, this, &OllamaModelAvailableWidget::slotRemoveModel);
}

OllamaModelAvailableWidget::~OllamaModelAvailableWidget() = default;

void OllamaModelAvailableWidget::slotRemoveModel()
{
    const auto currentIndex = mListView->currentIndex();
    if (currentIndex.isValid()) {
        // TODO update
    }
}

void OllamaModelAvailableWidget::slotClicked(const QModelIndex &index)
{
    if (!index.isValid()) {
        return;
    }
    mStackedWidget->setVisible(true);
    mStackedWidget->setCurrentWidget(mInfoWidget);
    mInfoWidget->generateWidget(index);
}

void OllamaModelAvailableWidget::slotDownloadModel(const QString &url)
{
    mStackedWidget->setCurrentWidget(mOllamaModelDownloadProgressWidget);
    mOllamaModelDownloadProgressWidget->downloadModel(url);
}

#include "moc_ollamamodelavailablewidget.cpp"
