/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextinstancesmcpserverwidget.h"
#include "widgets/mcpserver/textautogeneratetextmcpserverlistview.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QToolButton>

using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateTextInstancesMcpServerWidget::TextAutoGenerateTextInstancesMcpServerWidget(QWidget *parent)
    : QWidget{parent}
    , mSearchLineEdit(new QLineEdit(this))
    , mMcpServerListView(new TextAutoGenerateTextMcpServerListView(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins(QMargins{});
    mainLayout->setSpacing(0);

    auto hboxLayout = new QHBoxLayout;
    hboxLayout->setContentsMargins({});
    hboxLayout->setObjectName(u"hboxLayout"_s);

    mainLayout->addLayout(hboxLayout);

    mSearchLineEdit->setObjectName(u"mSearchLineEdit"_s);
    hboxLayout->addWidget(mSearchLineEdit);
    mSearchLineEdit->setClearButtonEnabled(true);
    mSearchLineEdit->setPlaceholderText(i18nc("@info:placeholder", "Search…"));
    KLineEditEventHandler::catchReturnKey(mSearchLineEdit);
    // connect(mSearchLineEdit, &QLineEdit::textChanged, mInstancesManagerListView, &TextAutoGenerateTextInstancesManagerListView::slotSearchChanged);

    auto addMcpServerButton = new QToolButton(this);
    addMcpServerButton->setObjectName(u"addMcpServerButton"_s);
    addMcpServerButton->setIcon(QIcon::fromTheme(u"list-add"_s));
    addMcpServerButton->setToolTip(i18nc("@info:tooltip", "Add Instance…"));
    addMcpServerButton->setAutoRaise(true);
    hboxLayout->addWidget(addMcpServerButton);
    // connect(addMcpServerButton, &QToolButton::clicked, this, &TextAutoGenerateTextInstancesManagerWidget::slotAddInstance);

    mMcpServerListView->setObjectName(u"mMcpServerListView"_s);
    mainLayout->addWidget(mMcpServerListView);
}

TextAutoGenerateTextInstancesMcpServerWidget::~TextAutoGenerateTextInstancesMcpServerWidget() = default;

#include "moc_textautogeneratetextinstancesmcpserverwidget.cpp"
