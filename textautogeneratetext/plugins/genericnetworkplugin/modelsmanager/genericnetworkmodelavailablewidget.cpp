/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkmodelavailablewidget.h"

#include "modelsmanager/genericnetworkmodelavailablelistview.h"
#include "widgets/common/textautogeneratemodelsearchlineedit.h"
#include <QSplitter>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
GenericNetworkModelAvailableWidget::GenericNetworkModelAvailableWidget(QWidget *parent)
    : QWidget{parent}
    , mAvailableListView(new GenericNetworkModelAvailableListView(this))
    , mSearchLineEdit(new TextAutoGenerateText::TextAutoGenerateModelSearchLineEdit(this))
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
    widget->setObjectName(u"splitter"_s);
    auto vboxLayout = new QVBoxLayout(widget);
    vboxLayout->setContentsMargins({});
    vboxLayout->setSpacing(0);
    vboxLayout->addWidget(mSearchLineEdit);
    vboxLayout->addWidget(mAvailableListView);

    splitter->addWidget(widget);
}

GenericNetworkModelAvailableWidget::~GenericNetworkModelAvailableWidget() = default;

#include "moc_genericnetworkmodelavailablewidget.cpp"
