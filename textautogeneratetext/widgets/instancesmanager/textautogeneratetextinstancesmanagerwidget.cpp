/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextinstancesmanagerwidget.h"
#include "textautogeneratetextinstancesmanagerlistview.h"
#include <KLineEditEventHandler>
#include <QLineEdit>
#include <QVBoxLayout>
#include <TextAutoGenerateText/TextAutoGenerateManager>

using namespace TextAutoGenerateText;
TextAutoGenerateTextInstancesManagerWidget::TextAutoGenerateTextInstancesManagerWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mInstancesManagerListView(new TextAutoGenerateTextInstancesManagerListView(manager, this))
    , mSearchLineEdit(new QLineEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(QMargins{});

    mSearchLineEdit->setObjectName(QStringLiteral("mSearchLineEdit"));
    mainLayout->addWidget(mSearchLineEdit);
    mSearchLineEdit->setClearButtonEnabled(true);
    KLineEditEventHandler::catchReturnKey(mSearchLineEdit);
    connect(mSearchLineEdit, &QLineEdit::textChanged, mInstancesManagerListView, &TextAutoGenerateTextInstancesManagerListView::slotSearchChanged);

    mInstancesManagerListView->setObjectName(QStringLiteral("mInstancesManagerListView"));
    mainLayout->addWidget(mInstancesManagerListView);
}

TextAutoGenerateTextInstancesManagerWidget::~TextAutoGenerateTextInstancesManagerWidget() = default;

#include "moc_textautogeneratetextinstancesmanagerwidget.cpp"
