/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserverwidget.h"
#include "addmcpserverdialog.h"
#include "mcpserverlistview.h"
#include "mcpserverwidget.h"
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
        TextAutoGenerateTextMcpProtocolCore::McpServer server;
        server.createUniqueIdentifier();
        const auto info = dlg->serverWidgetInfo();
        server.setServerUrl(QUrl(info.serverUrl));
        server.setName(info.name);
        mModel->addMcpServer(server);
    }
    delete dlg;
}

void McpServerWidget::slotRemoveServer(const QByteArray &identifier)
{
    mModel->removeMcpServer(identifier);
}

void McpServerWidget::slotEditServer(const QByteArray &identifier)
{
    QPointer<AddMcpServerDialog> dlg = new AddMcpServerDialog(this);
    const TextAutoGenerateTextMcpProtocolCore::McpServer mcpServer = mModel->mpcServer(identifier);
    const AddMcpServerWidget::McpServerWidgetInfo currentInfo{
        .name = mcpServer.name(),
        .serverUrl = mcpServer.serverUrl().toString(),
    };
    dlg->setServerWidgetInfo(currentInfo);
    if (dlg->exec()) {
        TextAutoGenerateTextMcpProtocolCore::McpServer server;
        server.createUniqueIdentifier();
        auto info = dlg->serverWidgetInfo();
        server.setServerUrl(QUrl(info.serverUrl));
        server.setName(info.name);
        mModel->addMcpServer(server);
    }
    delete dlg;
}

#include "moc_mcpserverwidget.cpp"
