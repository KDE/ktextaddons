/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkmodelavailablewidget.h"

#include "genericnetworkavailableinfosmodel.h"
#include "genericnetworkmanager.h"
#include "genericnetworkmodelavailableinfossortproxymodel.h"
#include "genericnetworkmodelavailablelistview.h"
#include "modelsmanager/genericnetworkmodelavailableinfowidget.h"
#include "widgets/common/textautogeneratemodelsearchlineedit.h"
#include <QSplitter>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
GenericNetworkModelAvailableWidget::GenericNetworkModelAvailableWidget(GenericNetworkManager *manager, QWidget *parent)
    : QWidget{parent}
    , mAvailableListView(new GenericNetworkModelAvailableListView(this))
    , mSearchLineEdit(new TextAutoGenerateText::TextAutoGenerateModelSearchLineEdit(this))
    , mAvailableInfosModel(new GenericNetworkAvailableInfosModel(this))
    , mProxyModel(new GenericNetworkModelAvailableInfosSortProxyModel(this))
    , mAvailableInfoWidget(new GenericNetworkModelAvailableInfoWidget(this))
    , mManager(manager)
{
    auto splitter = new QSplitter(this);
    splitter->setOrientation(Qt::Horizontal);
    splitter->setObjectName(u"splitter"_s);
    splitter->setChildrenCollapsible(false);

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainlayout"_s);
    mainLayout->setContentsMargins({});
    mainLayout->setSpacing(0);

    mainLayout->addWidget(splitter);

    auto widget = new QWidget(this);
    widget->setObjectName(u"widget"_s);
    auto vboxLayout = new QVBoxLayout(widget);
    vboxLayout->setContentsMargins({});
    vboxLayout->setSpacing(0);
    vboxLayout->addWidget(mSearchLineEdit);
    vboxLayout->addWidget(mAvailableListView);

    mProxyModel->setSourceModel(mAvailableInfosModel);
    mAvailableListView->setModel(mProxyModel);
    if (mManager) {
        mAvailableInfosModel->setModelInfos(mManager->infos());
    }

    splitter->addWidget(widget);

    mAvailableInfoWidget->setObjectName(u"mAvailableInfoWidget"_s);
    splitter->addWidget(mAvailableInfoWidget);
    connect(mSearchLineEdit, &TextAutoGenerateText::TextAutoGenerateModelSearchLineEdit::textChanged, this, [this](const QString &str) {
        mProxyModel->setFilterFixedString(str);
    });
}

GenericNetworkModelAvailableWidget::~GenericNetworkModelAvailableWidget() = default;

#include "moc_genericnetworkmodelavailablewidget.cpp"
