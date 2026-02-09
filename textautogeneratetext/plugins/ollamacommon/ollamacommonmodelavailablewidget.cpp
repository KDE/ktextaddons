/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamacommonmodelavailablewidget.h"
#include "ollamacommonmodelavailableinfossortproxymodel.h"
#include "ollamacommonmodelsinfoscategoriescombobox.h"
#include "widgets/availablemodel/textautogeneratemodelavailablelistview.h"
#include "widgets/common/textautogeneratemodelsearchlineedit.h"
#include <QSplitter>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
OllamaCommonModelAvailableWidget::OllamaCommonModelAvailableWidget(QWidget *parent)
    : QWidget{parent}
    , mAvailableListView(new TextAutoGenerateText::TextAutoGenerateModelAvailableListView(this))
    , mSearchLineEdit(new TextAutoGenerateText::TextAutoGenerateModelSearchLineEdit(this))
    , mCategoriesComboBox(new OllamaCommonModelsInfosCategoriesComboBox(this))
    , mProxyModel(new OllamaCommonModelAvailableInfosSortProxyModel(this))
{
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
    mainLayout->addWidget(splitter);

    mCategoriesComboBox->setObjectName(u"mCategoriesComboBox"_s);
    connect(mCategoriesComboBox, &OllamaCommonModelsInfosCategoriesComboBox::categoriesChanged, this, [this]() {
        mProxyModel->setCategories(mCategoriesComboBox->categories());
    });
    hboxLayout->addWidget(mSearchLineEdit);
    hboxLayout->addWidget(mCategoriesComboBox);

    mSearchLineEdit->setObjectName(u"mSearchLineEdit"_s);
    connect(mSearchLineEdit, &QLineEdit::textChanged, mProxyModel, &OllamaCommonModelAvailableInfosSortProxyModel::setFilterFixedString);
}

OllamaCommonModelAvailableWidget::~OllamaCommonModelAvailableWidget() = default;

#include "moc_ollamacommonmodelavailablewidget.cpp"
