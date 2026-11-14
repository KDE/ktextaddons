/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserverwidget.h"
#include "addmcpregistryserverdialog.h"
#include "addmcpserverdialog.h"
#include "importexport/mcpexportclaudecode.h"
#include "mcpserverlistview.h"
#include "models/mcpservermodel.h"
#include "textautogeneratetextmcpprotocol_widgets_debug.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <KMessageBox>
#include <KShell>
#include <QDir>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMenu>
#include <QPointer>
#include <QToolButton>
#include <TextAutoGenerateTextMcpProtocolCore/McpRegistryServerInfo>

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
    addMcpServerButton->setPopupMode(QToolButton::InstantPopup);
    hboxLayout->addWidget(addMcpServerButton);
    auto addServerMenu = new QMenu(addMcpServerButton);

    auto addServerAction = addServerMenu->addAction(i18nc("@action", "Add Server…"));

    addServerMenu->addSeparator();
    auto addFromRegistryAction = addServerMenu->addAction(QIcon::fromTheme(u"network-server"_s), i18nc("@action", "From MCP Registry…"));

    addServerMenu->addSeparator();
    auto importAction = addServerMenu->addAction(i18nc("@action", "Import…"));
    connect(importAction, &QAction::triggered, this, &McpServerWidget::slotImport);

    addMcpServerButton->setMenu(addServerMenu);

    connect(addServerAction, &QAction::triggered, this, &McpServerWidget::slotAddServer);
    connect(addFromRegistryAction, &QAction::triggered, this, &McpServerWidget::slotAddServerFromRegistry);

    mMcpServerListView->setObjectName(u"mMcpServerListView"_s);
    mainLayout->addWidget(mMcpServerListView);

    connect(mMcpServerListView, &McpServerListView::addServer, this, &McpServerWidget::slotAddServer);
    connect(mMcpServerListView, &McpServerListView::removeServer, this, &McpServerWidget::slotRemoveServer);
    connect(mMcpServerListView, &McpServerListView::editServer, this, &McpServerWidget::slotEditServer);
    connect(mMcpServerListView, &McpServerListView::exportServer, this, &McpServerWidget::slotExportServer);
    connect(mMcpServerListView, &McpServerListView::configureTools, this, &McpServerWidget::configureToolsRequested);
    connect(mMcpServerListView, &McpServerListView::importServer, this, &McpServerWidget::slotImport);
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

void McpServerWidget::setConfigureToolsSupported(bool supported)
{
    mMcpServerListView->setConfigureToolsSupported(supported);
}

TextAutoGenerateTextMcpProtocolCore::McpServer
McpServerWidget::convertMcpRegistryServerInfoToMcpServer(const TextAutoGenerateTextMcpProtocolCore::McpRegistryServerInfo &serverInfo)
{
    TextAutoGenerateTextMcpProtocolCore::McpServer server;
    server.createUniqueIdentifier();
    server.setName(serverInfo.displayName());

    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    // Prefer a remote endpoint: nothing to install locally
    const QList<TextAutoGenerateTextMcpProtocolCore::McpRegistryServerInfo::Remote> remotes = serverInfo.remotes();
    for (const auto &remote : remotes) {
        TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType type =
            TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Unknown;
        if (remote.type == "streamable-http"_L1) {
            type = TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::StreamableHttp;
        } else if (remote.type == "sse"_L1) {
            type = TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Sse;
        }
        if (type != TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Unknown) {
            server.setTransportType(type);
            settings.setServerUrl(QUrl(remote.url));
            server.setSettings(settings);
            return server;
        }
    }

    const QList<TextAutoGenerateTextMcpProtocolCore::McpRegistryServerInfo::Package> packages = serverInfo.packages();
    for (const auto &package : packages) {
        if (!package.transportType.isEmpty() && package.transportType != "stdio"_L1) {
            continue;
        }
        QString command;
        QStringList arguments;
        if (package.registryType == "npm"_L1) {
            command = u"npx"_s;
            arguments << u"-y"_s << (package.version.isEmpty() ? package.identifier : package.identifier + u'@' + package.version);
        } else if (package.registryType == "pypi"_L1) {
            command = u"uvx"_s;
            arguments << (package.version.isEmpty() ? package.identifier : package.identifier + u"=="_s + package.version);
        } else if (package.registryType == "oci"_L1) {
            command = u"docker"_s;
            arguments << u"run"_s << u"-i"_s << u"--rm"_s;
            for (const auto &env : package.environmentVariables) {
                arguments << u"-e"_s << env.name;
            }
            arguments << (package.version.isEmpty() ? package.identifier : package.identifier + u':' + package.version);
        } else {
            continue;
        }
        if (!package.runtimeHint.isEmpty()) {
            command = package.runtimeHint;
        }

        // Store only names: an empty value is not exported (user environment is used),
        // the user can fill them in the stdio settings
        QMap<QString, QString> environments;
        for (const auto &env : package.environmentVariables) {
            environments.insert(env.name, QString());
        }

        server.setTransportType(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Stdio);
        settings.setCommand(command);
        settings.setArguments(KShell::joinArgs(arguments));
        settings.setEnvironments(environments);
        server.setSettings(settings);
        return server;
    }
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOLWIDGETS_LOG) << "No supported remote or package found for" << serverInfo.name();
    return server;
}

void McpServerWidget::slotAddServerFromRegistry()
{
    if (!mModel) {
        return;
    }
    QPointer<AddMcpRegistryServerDialog> dlg = new AddMcpRegistryServerDialog(this);
    if (dlg->exec()) {
        const TextAutoGenerateTextMcpProtocolCore::McpServer server = convertMcpRegistryServerInfoToMcpServer(dlg->serverInfo());
        if (server.isValid()) {
            mModel->addMcpServer(server);
            Q_EMIT settingsChanged();
        } else {
            KMessageBox::error(this, i18n("This server does not provide a supported transport (remote or package)."), i18nc("@title:window", "Add MCP Server"));
        }
    }
    delete dlg;
}

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

void McpServerWidget::slotImport()
{
    // TODO
}

void McpServerWidget::slotExportServer(const QByteArray &identifier)
{
    if (!mModel) {
        return;
    }
    const TextAutoGenerateTextMcpProtocolCore::McpServer mcpServer = mModel->mcpServer(identifier);
    if (!mcpServer.isValid()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLWIDGETS_LOG) << "Invalid server for identifier:" << identifier;
        return;
    }
    // The server is merged into an existing file, so don't ask to overwrite it
    const QString filePath = QFileDialog::getSaveFileName(this,
                                                          i18nc("@title:window", "Export Server"),
                                                          QDir::homePath() + u"/.mcp.json"_s,
                                                          i18n("JSON Files (*.json)"),
                                                          nullptr,
                                                          QFileDialog::DontConfirmOverwrite);
    if (filePath.isEmpty()) {
        return;
    }
    TextAutoGenerateTextMcpProtocolCore::McpExportClaudeCode exportClaudeCode;
    exportClaudeCode.setPath(filePath);
    exportClaudeCode.setServer(mcpServer);
    if (!exportClaudeCode.exportServer()) {
        KMessageBox::error(this, i18n("An error occurred when exporting server."), i18nc("@title:window", "Export Server"));
    }
}

#include "moc_mcpserverwidget.cpp"
