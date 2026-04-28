/*
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "lmstudiomodelinstalledwidget.h"

#include "lmstudiomanager.h"
#include "lmstudiomodelinstalledinfosmodel.h"
#include "lmstudiomodelinstalledinfossortproxymodel.h"
#include "modelsmanager/lmstudiomodelinstalledinfosdelegate.h"
#include "modelsmanager/lmstudiomodelinstalledinfowidget.h"
#include "widgets/availablemodel/textautogeneratemodelavailablelistview.h"
#include "widgets/common/textautogeneratemodelsearchlineedit.h"
#include <QSplitter>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
LMStudioModelInstalledWidget::LMStudioModelInstalledWidget(LMStudioManager *manager, QWidget *parent)
    : QWidget{parent}
    , mInstalledListView(new TextAutoGenerateText::TextAutoGenerateModelAvailableListView(this))
    , mSearchLineEdit(new TextAutoGenerateText::TextAutoGenerateModelSearchLineEdit(this))
    , mInstalledInfosModel(new LMStudioModelInstalledInfosModel(this))
    , mProxyModel(new LMStudioModelInstalledInfosSortProxyModel(this))
    , mInstalledInfoWidget(new LMStudioModelInstalledInfoWidget(this))
    , mManager(manager)
{
    // TODO verify if we can move LMStudioModelInstalledInfosDelegate to lib
    mInstalledListView->setItemDelegate(new LMStudioModelInstalledInfosDelegate(mInstalledListView));
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
    vboxLayout->addWidget(mInstalledListView);

    mProxyModel->setSourceModel(mInstalledInfosModel);
    mInstalledListView->setModel(mProxyModel);
    mProxyModel->sort(0);
    if (mManager) {
        connect(mManager, &LMStudioManager::modelsLoadDone, this, [this]() {
            mInstalledInfosModel->setModelInstalledInfos(mManager->installedInfos());
        });
    }

    splitter->addWidget(widget);

    mInstalledInfoWidget->setObjectName(u"mInstalledInfoWidget"_s);
    splitter->addWidget(mInstalledInfoWidget);
    connect(mSearchLineEdit, &TextAutoGenerateText::TextAutoGenerateModelSearchLineEdit::textChanged, this, [this](const QString &str) {
        mProxyModel->setFilterFixedString(str);
    });
}

LMStudioModelInstalledWidget::~LMStudioModelInstalledWidget() = default;

#include "moc_lmstudiomodelinstalledwidget.cpp"
