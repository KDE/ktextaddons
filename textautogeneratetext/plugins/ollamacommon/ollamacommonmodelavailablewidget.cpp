/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamacommonmodelavailablewidget.h"
#include "ollamacommonmodelavailableinfosdelegate.h"
#include "ollamacommonmodelavailableinfosmodel.h"
#include "ollamacommonmodelavailableinfossortproxymodel.h"
#include "ollamacommonmodelavailableinfowidget.h"
#include "ollamacommonmodelsinfoscategoriescombobox.h"
#include "widgets/availablemodel/textautogeneratemodelavailablelistview.h"
#include "widgets/common/textautogeneratemodelsearchlineedit.h"
#include <QScrollArea>
#include <QSplitter>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
OllamaCommonModelAvailableWidget::OllamaCommonModelAvailableWidget(QWidget *parent)
    : QWidget{parent}
    , mAvailableListView(new TextAutoGenerateText::TextAutoGenerateModelAvailableListView(this))
    , mSearchLineEdit(new TextAutoGenerateText::TextAutoGenerateModelSearchLineEdit(this))
    , mCategoriesComboBox(new OllamaCommonModelsInfosCategoriesComboBox(this))
    , mProxyModel(new OllamaCommonModelAvailableInfosSortProxyModel(this))
    , mAvailableInfosModel(new OllamaCommonModelAvailableInfosModel(this))
    , mOllamaModelAvalaibleInfoWidget(new OllamaCommonModelAvailableInfoWidget(this))
{
    mAvailableListView->setItemDelegate(new OllamaCommonModelAvailableInfosDelegate(mAvailableListView));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainlayout"_s);
    mainLayout->setContentsMargins({});
    mainLayout->setSpacing(0);

    auto splitter = new QSplitter(this);
    splitter->setOrientation(Qt::Horizontal);
    splitter->setObjectName(u"splitter"_s);
    splitter->setChildrenCollapsible(false);

    auto widget = new QWidget(this);
    widget->setObjectName(u"widget"_s);

    auto hboxLayout = new QHBoxLayout;
    hboxLayout->setObjectName(u"hboxLayout"_s);
    hboxLayout->setContentsMargins({});
    hboxLayout->setSpacing(0);

    auto vboxLayout = new QVBoxLayout(widget);
    vboxLayout->setContentsMargins({});
    vboxLayout->setSpacing(0);
    vboxLayout->addLayout(hboxLayout);
    vboxLayout->addWidget(mAvailableListView);

    splitter->addWidget(widget);
    auto scrollArea = new QScrollArea(this);
    scrollArea->setObjectName(u"scrollArea"_s);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    splitter->addWidget(scrollArea);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(mOllamaModelAvalaibleInfoWidget);
    scrollArea->hide();
    mOllamaModelAvalaibleInfoWidget->setObjectName(u"mOllamaModelAvalaibleInfoWidget"_s);
    mainLayout->addWidget(splitter);

    mCategoriesComboBox->setObjectName(u"mCategoriesComboBox"_s);
    connect(mCategoriesComboBox, &OllamaCommonModelsInfosCategoriesComboBox::categoriesChanged, this, [this]() {
        mProxyModel->setCategories(mCategoriesComboBox->categories());
    });
    hboxLayout->addWidget(mSearchLineEdit);
    hboxLayout->addWidget(mCategoriesComboBox);

    mProxyModel->setSourceModel(mAvailableInfosModel);
    mAvailableListView->setModel(mProxyModel);

    mSearchLineEdit->setObjectName(u"mSearchLineEdit"_s);
    connect(mSearchLineEdit, &QLineEdit::textChanged, mProxyModel, &OllamaCommonModelAvailableInfosSortProxyModel::setFilterFixedString);
    connect(mAvailableListView, &TextAutoGenerateText::TextAutoGenerateModelAvailableListView::pressed, this, &OllamaCommonModelAvailableWidget::slotClicked);
    connect(mAvailableListView->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this, scrollArea]() {
        const bool isEnabled = mAvailableListView->currentIndex().isValid();
        scrollArea->setVisible(isEnabled);
    });
}

OllamaCommonModelAvailableWidget::~OllamaCommonModelAvailableWidget() = default;

void OllamaCommonModelAvailableWidget::slotClicked(const QModelIndex &index)
{
    if (index.isValid()) {
        qDebug() << " index " << index;
#if 0
        const OllamaModelInstalledInfo info = index.data(OllamaModelInstalledInfosModel::DescriptionInfo).value<OllamaModelInstalledInfo>();
        mOllamaModelInstalledInfoWidget->setOllamaModelInstalledInfo(info);
#endif
    }
}

void OllamaCommonModelAvailableWidget::setAvailableInfos(const QList<OllamaCommonModelAvailableInfo> &infos)
{
    mAvailableInfosModel->setModelInfos(infos);
}

#include "moc_ollamacommonmodelavailablewidget.cpp"
