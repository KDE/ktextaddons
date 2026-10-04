/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserverwidget.h"
#include "addmcpserverdialog.h"
#include "mcpserverlistview.h"
#include "models/mcpservermodel.h"
#include "textautogeneratetextmcpprotocol_widgets_debug.h"
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
    addMcpServerButton->setToolTip(i18nc("@info:tooltip", "Add Server…"));
    addMcpServerButton->setAutoRaise(true);
    hboxLayout->addWidget(addMcpServerButton);
    connect(addMcpServerButton, &QToolButton::clicked, this, &McpServerWidget::slotAddServer);

    mMcpServerListView->setObjectName(u"mMcpServerListView"_s);
    mainLayout->addWidget(mMcpServerListView);

    connect(mMcpServerListView, &McpServerListView::addServer, this, &McpServerWidget::slotAddServer);
    connect(mMcpServerListView, &McpServerListView::removeServer, this, &McpServerWidget::slotRemoveServer);
    connect(mMcpServerListView, &McpServerListView::editServer, this, &McpServerWidget::slotEditServer);
    if (mModel) {
        // Server was enabled/disabled from checkbox
        connect(mModel, &QAbstractItemModel::dataChanged, this, [this](const QModelIndex &, const QModelIndex &, const QList<int> &roles) {
            if (roles.contains(Qt::CheckStateRole)) {
                Q_EMIT settingsChanged();
            }
        });
    }
}

McpServerWidget::~McpServerWidget() = default;

void McpServerWidget::slotAddServer()
{
    if (!mModel) {
        return;
    }
    QPointer<AddMcpServerDialog> dlg = new AddMcpServerDialog(this);
    if (dlg->exec()) {
        mModel->addMcpServer(dlg->serverInfo());
        Q_EMIT settingsChanged();
    }
    delete dlg;
}

void McpServerWidget::slotRemoveServer(const QByteArray &identifier)
{
    if (!mModel) {
        return;
    }
    mModel->removeMcpServer(identifier);
    Q_EMIT settingsChanged();
}

void McpServerWidget::slotEditServer(const QByteArray &identifier)
{
    if (!mModel) {
        return;
    }
    const TextAutoGenerateTextMcpProtocolCore::McpServer mcpServer = mModel->mcpServer(identifier);
    if (!mcpServer.isValid()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLWIDGETS_LOG) << "Invalid server for identifier:" << identifier;
        return;
    }
    QPointer<AddMcpServerDialog> dlg = new AddMcpServerDialog(this);
    dlg->setServerInfo(mcpServer);
    if (dlg->exec()) {
        mModel->editMcpServer(dlg->serverInfo());
        Q_EMIT settingsChanged();
    }
    delete dlg;
}

#include "moc_mcpserverwidget.cpp"
