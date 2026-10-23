/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextconfiguremcpserverswidget.h"
#include "core/mcp/textautogeneratemcptoolsutils.h"
#include "core/textautogeneratemanager.h"
#include <KLocalizedString>
#include <QLabel>
#include <QListWidget>
#include <QSplitter>
#include <QVBoxLayout>
#include <TextAutoGenerateTextMcpProtocolCore/McpServerManager>
#include <TextAutoGenerateTextMcpProtocolCore/McpServerModel>
#include <TextAutoGenerateTextMcpProtocolWidgets/McpServerWidget>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateTextConfigureMcpServersWidget::TextAutoGenerateTextConfigureMcpServersWidget(TextAutoGenerateText::TextAutoGenerateManager *manager,
                                                                                             QWidget *parent)
    : QWidget{parent}
    , mManager(manager)
    , mMcpServerModel(new TextAutoGenerateTextMcpProtocolCore::McpServerModel(this))
    , mMcpServerWidget(new TextAutoGenerateTextMcpProtocolWidgets::McpServerWidget(mMcpServerModel, this))
    , mAlwaysAllowedListWidget(new QListWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    auto splitter = new QSplitter(this);
    splitter->setObjectName(u"splitter"_s);
    splitter->setChildrenCollapsible(false);
    splitter->setOrientation(Qt::Vertical);
    mainLayout->addWidget(splitter);

    mMcpServerWidget->setObjectName(u"mMcpServerWidget"_s);
    splitter->addWidget(mMcpServerWidget);
    connect(mMcpServerWidget,
            &TextAutoGenerateTextMcpProtocolWidgets::McpServerWidget::settingsChanged,
            this,
            &TextAutoGenerateTextConfigureMcpServersWidget::settingsChanged);

    auto widget = new QWidget(this);
    splitter->addWidget(widget);

    auto vboxLayout = new QVBoxLayout(widget);
    vboxLayout->setObjectName(u"vboxLayout"_s);
    vboxLayout->setContentsMargins({});

    auto alwaysAllowedLabel = new QLabel(i18nc("@label", "Run tools without confirmation:"), this);
    alwaysAllowedLabel->setObjectName(u"alwaysAllowedLabel"_s);
    vboxLayout->addWidget(alwaysAllowedLabel);

    mAlwaysAllowedListWidget->setObjectName(u"mAlwaysAllowedListWidget"_s);
    alwaysAllowedLabel->setBuddy(mAlwaysAllowedListWidget);
    vboxLayout->addWidget(mAlwaysAllowedListWidget);
    connect(mAlwaysAllowedListWidget, &QListWidget::itemChanged, this, &TextAutoGenerateTextConfigureMcpServersWidget::settingsChanged);

    // Follow list of servers edited in widget
    connect(mMcpServerModel, &QAbstractItemModel::modelReset, this, &TextAutoGenerateTextConfigureMcpServersWidget::updateAlwaysAllowedServers);
    connect(mMcpServerModel, &QAbstractItemModel::rowsInserted, this, &TextAutoGenerateTextConfigureMcpServersWidget::updateAlwaysAllowedServers);
    connect(mMcpServerModel, &QAbstractItemModel::rowsRemoved, this, &TextAutoGenerateTextConfigureMcpServersWidget::updateAlwaysAllowedServers);
    connect(mMcpServerModel, &QAbstractItemModel::dataChanged, this, &TextAutoGenerateTextConfigureMcpServersWidget::updateAlwaysAllowedServers);
    load();
}

TextAutoGenerateTextConfigureMcpServersWidget::~TextAutoGenerateTextConfigureMcpServersWidget() = default;

void TextAutoGenerateTextConfigureMcpServersWidget::load()
{
    if (mManager) {
        // Load allowed servers first: list is created when model is reset
        const QList<QByteArray> alwaysAllowedServers =
            TextAutoGenerateMcpToolsUtils::alwaysAllowedServers(mManager->textAutoGenerateTextMcpServerManager()->serverConfigFileName());
        mAlwaysAllowedListWidget->clear();
        mMcpServerModel->setMcpServers(mManager->textAutoGenerateTextMcpServerManager()->mcpServerModel()->mcpServers());
        const QSignalBlocker blocker(mAlwaysAllowedListWidget);
        for (int i = 0; i < mAlwaysAllowedListWidget->count(); ++i) {
            QListWidgetItem *item = mAlwaysAllowedListWidget->item(i);
            const bool allowed = alwaysAllowedServers.contains(item->data(Qt::UserRole).toByteArray());
            item->setCheckState(allowed ? Qt::Checked : Qt::Unchecked);
        }
    }
}

QList<QByteArray> TextAutoGenerateTextConfigureMcpServersWidget::checkedAlwaysAllowedServers() const
{
    QList<QByteArray> identifiers;
    for (int i = 0; i < mAlwaysAllowedListWidget->count(); ++i) {
        const QListWidgetItem *item = mAlwaysAllowedListWidget->item(i);
        if (item->checkState() == Qt::Checked) {
            identifiers.append(item->data(Qt::UserRole).toByteArray());
        }
    }
    return identifiers;
}

void TextAutoGenerateTextConfigureMcpServersWidget::updateAlwaysAllowedServers()
{
    // Keep state of servers which are still in list
    const QList<QByteArray> checkedServers = checkedAlwaysAllowedServers();
    const QSignalBlocker blocker(mAlwaysAllowedListWidget);
    mAlwaysAllowedListWidget->clear();
    const auto servers = mMcpServerModel->mcpServers();
    for (const auto &server : servers) {
        auto item = new QListWidgetItem(server.name(), mAlwaysAllowedListWidget);
        item->setData(Qt::UserRole, server.identifier());
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(checkedServers.contains(server.identifier()) ? Qt::Checked : Qt::Unchecked);
    }
}

void TextAutoGenerateTextConfigureMcpServersWidget::save()
{
    if (!mManager) {
        return;
    }
    auto serverManager = mManager->textAutoGenerateTextMcpServerManager();
    // Connections of modified servers are closed by TextAutoGenerateMcpToolsManager
    serverManager->mcpServerModel()->setMcpServers(mMcpServerModel->mcpServers());
    serverManager->saveServers();
    // Removed servers are removed from list too
    TextAutoGenerateMcpToolsUtils::setAlwaysAllowedServers(serverManager->serverConfigFileName(), checkedAlwaysAllowedServers());
}

#include "moc_textautogeneratetextconfiguremcpserverswidget.cpp"
