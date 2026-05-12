/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserverwidget.h"
#include "addmcpserverdialog.h"
#include "mcpserverlistview.h"
#include "models/mcpservermodel.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPointer>
#include <QToolButton>

using namespace TextAutoGenerateTextMcpProtocolWidgets;
using namespace Qt::Literals::StringLiterals;
McpServerWidget::McpServerWidget(TextAutoGenerateTextMcpProtocolCore::McpServerModel *model, QWidget *parent)
    : QWidget{parent}
    , mSearchLineEdit(new QLineEdit(this))
    , mMcpServerListView(new McpServerListView(model, this))
    , mModel(model)
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
    connect(mSearchLineEdit, &QLineEdit::textChanged, mMcpServerListView, &McpServerListView::slotSearchChanged);

    auto addMcpServerButton = new QToolButton(this);
    addMcpServerButton->setObjectName(u"addMcpServerButton"_s);
    addMcpServerButton->setIcon(QIcon::fromTheme(u"list-add"_s));
    addMcpServerButton->setToolTip(i18nc("@info:tooltip", "Add Instance…"));
    addMcpServerButton->setAutoRaise(true);
    hboxLayout->addWidget(addMcpServerButton);
    connect(addMcpServerButton, &QToolButton::clicked, this, &McpServerWidget::slotAddServer);

    mMcpServerListView->setObjectName(u"mMcpServerListView"_s);
    mainLayout->addWidget(mMcpServerListView);

    connect(mMcpServerListView, &McpServerListView::addServer, this, &McpServerWidget::slotAddServer);
    connect(mMcpServerListView, &McpServerListView::removeServer, this, &McpServerWidget::slotRemoveServer);
    connect(mMcpServerListView, &McpServerListView::editServer, this, &McpServerWidget::slotEditServer);
}

McpServerWidget::~McpServerWidget() = default;

void McpServerWidget::slotAddServer()
{
    QPointer<AddMcpServerDialog> dlg = new AddMcpServerDialog(this);
    if (dlg->exec()) {
        const auto info = dlg->serverInfo();
        mModel->addMcpServer(info);
        Q_EMIT settingsChanged();
    }
    delete dlg;
}

void McpServerWidget::slotRemoveServer(const QByteArray &identifier)
{
    mModel->removeMcpServer(identifier);
    Q_EMIT settingsChanged();
}

void McpServerWidget::slotEditServer(const QByteArray &identifier)
{
    QPointer<AddMcpServerDialog> dlg = new AddMcpServerDialog(this);
    const TextAutoGenerateTextMcpProtocolCore::McpServer mcpServer = mModel->mpcServer(identifier);
    dlg->setServerInfo(mcpServer);
    if (dlg->exec()) {
        const auto info = dlg->serverInfo();
        mModel->editMcpServer(info);
        Q_EMIT settingsChanged();
    }
    delete dlg;
}

#include "moc_mcpserverwidget.cpp"
