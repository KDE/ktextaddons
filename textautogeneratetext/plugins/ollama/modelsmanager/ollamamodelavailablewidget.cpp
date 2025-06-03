/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelavailablewidget.h"
#include "modelsmanager/ollamamodeldownloadfromnamedialog.h"
#include "ollamamodelavailableinfosmodel.h"
#include "ollamamodelavailableinfossortproxymodel.h"
#include "ollamamodelavailableinfowidget.h"
#include "ollamamodelavailablelistview.h"
#include "ollamamodelavailablesearchwidget.h"
#include "ollamamodeldownloadprogresswidget.h"
#include <QScrollArea>
#include <QSplitter>
#include <QStackedWidget>
#include <QVBoxLayout>

OllamaModelAvailableWidget::OllamaModelAvailableWidget(OllamaManager *manager, QWidget *parent)
    : QWidget{parent}
    , mSearchWidget(new OllamaModelAvailableSearchWidget(this))
    , mListView(new OllamaModelAvailableListView(this))
    , mInfoWidget(new OllamaModelAvailableInfoWidget(manager, this))
    , mProxyModel(new OllamaModelAvailableInfosSortProxyModel(this))
    , mOllamaModelDownloadProgressWidget(new OllamaModelDownloadProgressWidget(manager, this))
    , mStackedWidget(new QStackedWidget(this))
    , mAvailableInfosModel(new OllamaModelAvailableInfosModel(this))
    , mScrollArea(new QScrollArea(this))
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

    mScrollArea->setObjectName(QStringLiteral("mScrollArea"));
    mScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mScrollArea->setWidgetResizable(true);
    mScrollArea->setWidget(mInfoWidget);
    mInfoWidget->setObjectName(QStringLiteral("mInfoWidget"));
    splitter->addWidget(mStackedWidget);
    mStackedWidget->hide();

    mOllamaModelDownloadProgressWidget->setObjectName(QStringLiteral("mOllamaModelDownloadProgressWidget"));
    mStackedWidget->setObjectName(QStringLiteral("mStackedWidget"));
    mStackedWidget->addWidget(mScrollArea);
    mStackedWidget->addWidget(mOllamaModelDownloadProgressWidget);
    mStackedWidget->setCurrentWidget(mScrollArea);
    connect(mInfoWidget, &OllamaModelAvailableInfoWidget::downloadModel, this, &OllamaModelAvailableWidget::slotDownloadModel);

    mProxyModel->setSourceModel(mAvailableInfosModel);
    mListView->setModel(mProxyModel);
    connect(mSearchWidget, &OllamaModelAvailableSearchWidget::searchText, mProxyModel, &OllamaModelAvailableInfosSortProxyModel::setFilterFixedString);
    connect(mSearchWidget, &OllamaModelAvailableSearchWidget::categoriesChanged, mProxyModel, &OllamaModelAvailableInfosSortProxyModel::setCategories);
    connect(mListView, &OllamaModelAvailableListView::clicked, this, &OllamaModelAvailableWidget::slotClicked);
    connect(mSearchWidget, &OllamaModelAvailableSearchWidget::addModel, this, &OllamaModelAvailableWidget::slotAddModel);
}

OllamaModelAvailableWidget::~OllamaModelAvailableWidget() = default;

void OllamaModelAvailableWidget::setAvailableInfos(const QList<OllamaModelAvailableInfo> &infos)
{
    mAvailableInfosModel->setModelInfos(infos);
}

void OllamaModelAvailableWidget::slotAddModel()
{
    OllamaModelDownloadFromNameDialog d(this);
    if (d.exec()) {
        const QString modelName = d.modelName().trimmed();
        if (!modelName.isEmpty()) {
            // TODO implement download
        }
    }
}

void OllamaModelAvailableWidget::slotClicked(const QModelIndex &index)
{
    if (!index.isValid()) {
        return;
    }
    mStackedWidget->setVisible(true);
    mStackedWidget->setCurrentWidget(mScrollArea);
    mInfoWidget->generateWidget(index);
}

void OllamaModelAvailableWidget::slotDownloadModel(const QString &url)
{
    mStackedWidget->setCurrentWidget(mOllamaModelDownloadProgressWidget);
    mOllamaModelDownloadProgressWidget->downloadModel(url);
}

#include "moc_ollamamodelavailablewidget.cpp"
