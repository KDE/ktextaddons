/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratemcpservertoolswidget.h"
#include "core/mcp/textautogeneratemcptoolsmanager.h"
#include "core/mcp/textautogeneratemcptoolsutils.h"
#include "core/textautogeneratemanager.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <TextAutoGenerateTextMcpProtocolCore/McpServerManager>
#include <TextAutoGenerateTextMcpProtocolCore/McpServerModel>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateMcpServerToolsWidget::TextAutoGenerateMcpServerToolsWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mManager(manager)
    , mFilterToolsCheckBox(new QCheckBox(i18nc("@option:check", "Only allow selected tools"), this))
    , mSearchLineEdit(new QLineEdit(this))
    , mToolsListWidget(new QListWidget(this))
    , mStatusLabel(new QLabel(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mFilterToolsCheckBox->setObjectName(u"mFilterToolsCheckBox"_s);
    mFilterToolsCheckBox->setToolTip(i18nc("@info:tooltip", "Tools which are not selected are not sent to LLM. New tools of server are not allowed."));
    mainLayout->addWidget(mFilterToolsCheckBox);

    auto hboxLayout = new QHBoxLayout;
    hboxLayout->setObjectName(u"hboxLayout"_s);
    hboxLayout->setContentsMargins({});
    mainLayout->addLayout(hboxLayout);

    mSearchLineEdit->setObjectName(u"mSearchLineEdit"_s);
    mSearchLineEdit->setClearButtonEnabled(true);
    mSearchLineEdit->setPlaceholderText(i18nc("@info:placeholder", "Search…"));
    KLineEditEventHandler::catchReturnKey(mSearchLineEdit);
    hboxLayout->addWidget(mSearchLineEdit);

    auto selectAllButton = new QPushButton(i18nc("@action:button", "Select All"), this);
    selectAllButton->setObjectName(u"selectAllButton"_s);
    hboxLayout->addWidget(selectAllButton);

    auto unselectAllButton = new QPushButton(i18nc("@action:button", "Unselect All"), this);
    unselectAllButton->setObjectName(u"unselectAllButton"_s);
    hboxLayout->addWidget(unselectAllButton);

    mToolsListWidget->setObjectName(u"mToolsListWidget"_s);
    mainLayout->addWidget(mToolsListWidget);

    mStatusLabel->setObjectName(u"mStatusLabel"_s);
    mStatusLabel->setWordWrap(true);
    mainLayout->addWidget(mStatusLabel);

    const auto updateEnabled = [this, selectAllButton, unselectAllButton](bool filter) {
        mSearchLineEdit->setEnabled(filter);
        mToolsListWidget->setEnabled(filter);
        selectAllButton->setEnabled(filter);
        unselectAllButton->setEnabled(filter);
    };
    updateEnabled(false);
    connect(mFilterToolsCheckBox, &QCheckBox::toggled, this, updateEnabled);
    connect(mSearchLineEdit, &QLineEdit::textChanged, this, &TextAutoGenerateMcpServerToolsWidget::slotSearchChanged);
    connect(selectAllButton, &QPushButton::clicked, this, [this]() {
        setAllChecked(true);
    });
    connect(unselectAllButton, &QPushButton::clicked, this, [this]() {
        setAllChecked(false);
    });
    connect(mToolsListWidget, &QListWidget::itemChanged, this, [this](QListWidgetItem *item) {
        const QString name = item->data(Qt::UserRole).toString();
        mAllowedTools.removeAll(name);
        if (item->checkState() == Qt::Checked) {
            mAllowedTools.append(name);
        }
    });

    if (mManager) {
        auto toolsManager = mManager->textAutoGenerateMcpToolsManager();
        connect(toolsManager, &TextAutoGenerateMcpToolsManager::toolsChanged, this, [this](const QByteArray &identifier) {
            if (identifier == mServer.identifier()) {
                updateTools();
            }
        });
        connect(toolsManager, &TextAutoGenerateMcpToolsManager::statusChanged, this, [this](const QByteArray &identifier) {
            if (identifier == mServer.identifier()) {
                updateStatus();
            }
        });
    }
}

TextAutoGenerateMcpServerToolsWidget::~TextAutoGenerateMcpServerToolsWidget() = default;

void TextAutoGenerateMcpServerToolsWidget::setServer(const TextAutoGenerateTextMcpProtocolCore::McpServer &server)
{
    mServer = server;
    mAllowedTools = server.allowedTools();
    mFilterToolsCheckBox->setChecked(server.filterTools());
    updateTools();
    updateStatus();
    if (canListTools()) {
        // Tools are known when server is connected
        mManager->textAutoGenerateMcpToolsManager()->connectServer(mServer.identifier());
    }
}

TextAutoGenerateTextMcpProtocolCore::McpServer TextAutoGenerateMcpServerToolsWidget::server() const
{
    TextAutoGenerateTextMcpProtocolCore::McpServer server = mServer;
    server.setFilterTools(mFilterToolsCheckBox->isChecked());
    server.setAllowedTools(mAllowedTools);
    return server;
}

bool TextAutoGenerateMcpServerToolsWidget::canListTools() const
{
    if (!mManager || !mServer.enabled() || !mServer.isValid()) {
        return false;
    }
    // Connection uses saved server: modified server must be saved first
    const auto savedServer = mManager->textAutoGenerateTextMcpServerManager()->mcpServerModel()->mcpServer(mServer.identifier());
    return TextAutoGenerateMcpToolsUtils::sameConnectionSettings(savedServer, mServer);
}

void TextAutoGenerateMcpServerToolsWidget::updateStatus()
{
    if (!canListTools()) {
        mStatusLabel->setText(mServer.enabled() ? i18n("Apply changes to load the list of tools of this server.")
                                                : i18n("Enable this server to load the list of its tools."));
        return;
    }
    auto toolsManager = mManager->textAutoGenerateMcpToolsManager();
    const QByteArray identifier = mServer.identifier();
    switch (toolsManager->status(identifier)) {
    case TextAutoGenerateMcpToolsManager::Status::Disconnected:
        mStatusLabel->setText(i18n("Not connected"));
        break;
    case TextAutoGenerateMcpToolsManager::Status::Connecting:
        mStatusLabel->setText(i18n("Connecting…"));
        break;
    case TextAutoGenerateMcpToolsManager::Status::Connected:
        if (toolsManager->isReady(identifier)) {
            mStatusLabel->clear();
        } else {
            mStatusLabel->setText(i18n("Loading tools…"));
        }
        break;
    case TextAutoGenerateMcpToolsManager::Status::Error:
        mStatusLabel->setText(i18n("Error: %1", toolsManager->errorString(identifier)));
        break;
    }
}

void TextAutoGenerateMcpServerToolsWidget::updateTools()
{
    const QSignalBlocker blocker(mToolsListWidget);
    mToolsListWidget->clear();
    QStringList toolNames;
    if (canListTools()) {
        auto tools = mManager->textAutoGenerateMcpToolsManager()->allTools(mServer.identifier());
        std::sort(tools.begin(), tools.end(), [](const TextAutoGenerateMcpToolsManager::McpTool &left, const TextAutoGenerateMcpToolsManager::McpTool &right) {
            return left.name < right.name;
        });
        for (const auto &tool : std::as_const(tools)) {
            auto item = new QListWidgetItem(QIcon::fromTheme(TextAutoGenerateMcpToolsUtils::toolRiskIconName(tool.risk)),
                                            tool.displayName.isEmpty() ? tool.name : tool.displayName,
                                            mToolsListWidget);
            const QString riskText = TextAutoGenerateMcpToolsUtils::toolRiskText(tool.risk);
            if (tool.description.isEmpty()) {
                item->setToolTip(u"<qt><b>%1</b></qt>"_s.arg(riskText.toHtmlEscaped()));
            } else {
                item->setToolTip(u"<qt>%1<br /><b>%2</b></qt>"_s.arg(tool.description.toHtmlEscaped(), riskText.toHtmlEscaped()));
            }
            item->setData(Qt::UserRole, tool.name);
            toolNames.append(tool.name);
        }
    }
    // Allowed tools which are not provided by server (unknown list of tools, tool removed from server)
    for (const QString &name : std::as_const(mAllowedTools)) {
        if (!toolNames.contains(name)) {
            auto item = new QListWidgetItem(name, mToolsListWidget);
            item->setData(Qt::UserRole, name);
        }
    }
    for (int i = 0; i < mToolsListWidget->count(); ++i) {
        QListWidgetItem *item = mToolsListWidget->item(i);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(mAllowedTools.contains(item->data(Qt::UserRole).toString()) ? Qt::Checked : Qt::Unchecked);
    }
    slotSearchChanged(mSearchLineEdit->text());
}

void TextAutoGenerateMcpServerToolsWidget::slotSearchChanged(const QString &str)
{
    for (int i = 0; i < mToolsListWidget->count(); ++i) {
        QListWidgetItem *item = mToolsListWidget->item(i);
        const bool match =
            str.isEmpty() || item->text().contains(str, Qt::CaseInsensitive) || item->data(Qt::UserRole).toString().contains(str, Qt::CaseInsensitive);
        item->setHidden(!match);
    }
}

void TextAutoGenerateMcpServerToolsWidget::setAllChecked(bool checked)
{
    // Only visible tools: select result of search
    for (int i = 0; i < mToolsListWidget->count(); ++i) {
        QListWidgetItem *item = mToolsListWidget->item(i);
        if (!item->isHidden()) {
            item->setCheckState(checked ? Qt::Checked : Qt::Unchecked);
        }
    }
}

#include "moc_textautogeneratemcpservertoolswidget.cpp"
