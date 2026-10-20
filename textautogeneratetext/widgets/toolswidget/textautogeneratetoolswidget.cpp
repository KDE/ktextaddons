/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetoolswidget.h"
#include "core/mcp/textautogeneratemcptoolsmanager.h"
#include "core/textautogeneratemanager.h"
#include "core/tools/textautogeneratetexttoolpluginmanager.h"
#include "textautogeneratetextwidget_debug.h"
#include <KLocalizedString>
#include <QLabel>
#include <QMenu>
#include <QToolButton>
#include <TextAddonsWidgets/TextAddonsWidgetFlowLayout>
#include <TextAutoGenerateTextMcpProtocolCore/McpServerManager>
#include <TextAutoGenerateTextMcpProtocolCore/McpServerModel>
#include <tuple>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
namespace
{
constexpr const char *button_property("identifier");

QString toolRiskIconName(TextAutoGenerateMcpToolsManager::ToolRisk risk)
{
    switch (risk) {
    case TextAutoGenerateMcpToolsManager::ToolRisk::ReadOnly:
        return u"security-high"_s;
    case TextAutoGenerateMcpToolsManager::ToolRisk::Modify:
        return u"security-medium"_s;
    case TextAutoGenerateMcpToolsManager::ToolRisk::Destructive:
        return u"security-low"_s;
    }
    return {};
}

QString toolRiskText(TextAutoGenerateMcpToolsManager::ToolRisk risk)
{
    switch (risk) {
    case TextAutoGenerateMcpToolsManager::ToolRisk::ReadOnly:
        return i18n("Read-only");
    case TextAutoGenerateMcpToolsManager::ToolRisk::Modify:
        return i18n("Modifies data");
    case TextAutoGenerateMcpToolsManager::ToolRisk::Destructive:
        return i18n("May delete or overwrite data");
    }
    return {};
}
}
TextAutoGenerateToolsWidget::TextAutoGenerateToolsWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mManager(manager)
{
    auto mainLayout = new TextAddonsWidgets::TextAddonsWidgetFlowLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    auto label = new QLabel(i18nc("@label:textbox", "Tools:"), this);
    label->setObjectName(u"label"_s);
    QFont f = label->font();
    f.setBold(true);
    label->setFont(f);
    mainLayout->addWidget(label);
    mainLayout->setAlignment(label, Qt::AlignBottom);
    mainLayout->setHorizontalSpacing(0);

    const QList<TextAutoGenerateTextToolPluginManager::PluginToolInfo> lst = TextAutoGenerateTextToolPluginManager::self()->activePluginTools();
    mListButton.reserve(lst.count());
    for (const auto &info : lst) {
        auto b = new QToolButton(this);
        b->setToolTip(info.description);
        b->setText(info.displayName);
        b->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        b->setAutoRaise(true);
        if (!info.iconName.isEmpty()) {
            b->setIcon(QIcon::fromTheme(info.iconName));
        }
        b->setProperty(button_property, info.identifier);
        b->setCheckable(true);
        mainLayout->addWidget(b);
        mListButton.append(b);
    }
    if (mManager) {
        createMcpServerButtons();
        // Servers added, removed or modified
        auto model = mManager->textAutoGenerateTextMcpServerManager()->mcpServerModel();
        connect(model, &QAbstractItemModel::modelReset, this, &TextAutoGenerateToolsWidget::createMcpServerButtons);
        connect(model, &QAbstractItemModel::rowsInserted, this, &TextAutoGenerateToolsWidget::createMcpServerButtons);
        connect(model, &QAbstractItemModel::rowsRemoved, this, &TextAutoGenerateToolsWidget::createMcpServerButtons);
        connect(model, &QAbstractItemModel::dataChanged, this, &TextAutoGenerateToolsWidget::createMcpServerButtons);
        auto toolsManager = mManager->textAutoGenerateMcpToolsManager();
        connect(toolsManager, &TextAutoGenerateMcpToolsManager::statusChanged, this, &TextAutoGenerateToolsWidget::updateMcpServerButton);
        connect(toolsManager, &TextAutoGenerateMcpToolsManager::toolsChanged, this, &TextAutoGenerateToolsWidget::updateMcpServerButton);
    }
}

void TextAutoGenerateToolsWidget::createMcpServerButtons()
{
    // Keep selected servers
    QList<QByteArray> checkedServers;
    for (auto b : std::as_const(mMcpServerButtons)) {
        if (b->isChecked()) {
            checkedServers.append(b->property(button_property).toByteArray());
        }
        mListButton.removeAll(b);
        delete b;
    }
    mMcpServerButtons.clear();
    const auto servers = mManager->textAutoGenerateTextMcpServerManager()->mcpServerModel()->mcpServers();
    QHash<QByteArray, QStringList> selectedTools;
    for (const auto &server : servers) {
        if (!server.enabled() || !server.isValid()) {
            continue;
        }
        const QByteArray serverIdentifier = server.identifier();
        if (const auto it = mMcpSelectedTools.constFind(serverIdentifier); it != mMcpSelectedTools.cend()) {
            selectedTools.insert(serverIdentifier, *it);
        }
        auto b = new QToolButton(this);
        b->setText(server.name());
        b->setIcon(server.iconName().isEmpty() ? QIcon::fromTheme(u"network-server-symbolic"_s) : QIcon::fromTheme(server.iconName()));
        b->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        b->setAutoRaise(true);
        b->setCheckable(true);
        b->setProperty(button_property, TextAutoGenerateMcpToolsManager::toolIdentifier(serverIdentifier));
        // Menu allows to select tools of server
        auto menu = new QMenu(b);
        b->setMenu(menu);
        b->setPopupMode(QToolButton::MenuButtonPopup);
        connect(menu, &QMenu::aboutToShow, this, [this, serverIdentifier]() {
            // Tools are known when server is connected
            mManager->textAutoGenerateMcpToolsManager()->connectServer(serverIdentifier);
        });
        connect(b, &QToolButton::toggled, this, [this, serverIdentifier](bool checked) {
            if (checked) {
                // No tool selected: use all tools again
                if (const auto it = mMcpSelectedTools.constFind(serverIdentifier); it != mMcpSelectedTools.cend() && it->isEmpty()) {
                    mMcpSelectedTools.remove(serverIdentifier);
                    updateMcpServerButton(serverIdentifier);
                }
                // Connect now: tools will be ready when message is sent
                mManager->textAutoGenerateMcpToolsManager()->connectServer(serverIdentifier);
            }
        });
        layout()->addWidget(b);
        mListButton.append(b);
        mMcpServerButtons.append(b);
        b->setChecked(checkedServers.contains(b->property(button_property).toByteArray()));
    }
    // Forget selection of removed servers
    mMcpSelectedTools = selectedTools;
    for (const auto &server : servers) {
        updateMcpServerButton(server.identifier());
    }
}

void TextAutoGenerateToolsWidget::updateMcpServerButton(const QByteArray &serverIdentifier)
{
    const QByteArray identifier = TextAutoGenerateMcpToolsManager::toolIdentifier(serverIdentifier);
    const auto it = std::find_if(mMcpServerButtons.cbegin(), mMcpServerButtons.cend(), [identifier](QToolButton *b) {
        return b->property(button_property).toByteArray() == identifier;
    });
    if (it == mMcpServerButtons.cend()) {
        return;
    }
    auto toolsManager = mManager->textAutoGenerateMcpToolsManager();
    QString status;
    switch (toolsManager->status(serverIdentifier)) {
    case TextAutoGenerateMcpToolsManager::Status::Disconnected:
        status = i18n("Not connected");
        break;
    case TextAutoGenerateMcpToolsManager::Status::Connecting:
        status = i18n("Connecting…");
        break;
    case TextAutoGenerateMcpToolsManager::Status::Connected:
        if (toolsManager->isReady(serverIdentifier)) {
            status = i18np("1 tool", "%1 tools", toolsManager->tools(serverIdentifier).count());
        } else {
            status = i18n("Loading tools…");
        }
        break;
    case TextAutoGenerateMcpToolsManager::Status::Error:
        status = i18n("Error: %1", toolsManager->errorString(serverIdentifier));
        break;
    }
    (*it)->setToolTip(i18n("Tools of MCP server \"%1\" (%2)", (*it)->text(), status));
    fillMcpToolsMenu(*it, serverIdentifier, status);
}

void TextAutoGenerateToolsWidget::fillMcpToolsMenu(QToolButton *button, const QByteArray &serverIdentifier, const QString &status)
{
    QMenu *menu = button->menu();
    menu->clear();
    auto tools = mManager->textAutoGenerateMcpToolsManager()->tools(serverIdentifier);
    if (tools.isEmpty()) {
        auto action = menu->addAction(status);
        action->setEnabled(false);
        return;
    }
    // Tools without group first, then tools grouped by _meta group
    std::sort(tools.begin(), tools.end(), [](const TextAutoGenerateMcpToolsManager::McpTool &left, const TextAutoGenerateMcpToolsManager::McpTool &right) {
        return std::tie(left.groupName, left.name) < std::tie(right.groupName, right.name);
    });
    const auto it = mMcpSelectedTools.constFind(serverIdentifier);
    QString currentGroupName;
    for (const auto &tool : tools) {
        if (tool.groupName != currentGroupName) {
            currentGroupName = tool.groupName;
            menu->addSection(tool.groupTitle.isEmpty() ? tool.groupName : tool.groupTitle);
        }
        auto action = menu->addAction(tool.displayName.isEmpty() ? tool.name : tool.displayName);
        action->setIcon(QIcon::fromTheme(toolRiskIconName(tool.risk)));
        const QString riskText = toolRiskText(tool.risk);
        QString tooltipStr;
        if (tool.description.isEmpty()) {
            tooltipStr = u"<qt><b>%1</b></qt>"_s.arg(riskText.toHtmlEscaped());
        } else {
            tooltipStr = u"<qt>%1<br /><b>%2</b></qt>"_s.arg(tool.description.toHtmlEscaped(), riskText.toHtmlEscaped());
        }
        action->setToolTip(tooltipStr);
        action->setData(tool.name);
        action->setCheckable(true);
        action->setChecked(it == mMcpSelectedTools.cend() || it->contains(tool.name));
        connect(action, &QAction::toggled, this, [this, button, serverIdentifier]() {
            slotMcpToolToggled(button, serverIdentifier);
        });
    }
    menu->setToolTipsVisible(true);
}

void TextAutoGenerateToolsWidget::slotMcpToolToggled(QToolButton *button, const QByteArray &serverIdentifier)
{
    const auto actions = button->menu()->actions();
    QStringList toolNames;
    qsizetype toolCount = 0;
    for (const auto action : actions) {
        // Skip group sections
        if (!action->isCheckable()) {
            continue;
        }
        ++toolCount;
        if (action->isChecked()) {
            toolNames.append(action->data().toString());
        }
    }
    if (toolNames.count() == toolCount) {
        mMcpSelectedTools.remove(serverIdentifier);
    } else {
        mMcpSelectedTools.insert(serverIdentifier, toolNames);
    }
    // Selecting a tool selects server
    button->setChecked(!toolNames.isEmpty());
}

TextAutoGenerateToolsWidget::~TextAutoGenerateToolsWidget() = default;

QList<QByteArray> TextAutoGenerateToolsWidget::generateListOfActiveTools() const
{
    QList<QByteArray> activeTools;
    activeTools.reserve(mListButton.count());
    for (const auto b : std::as_const(mListButton)) {
        if (b->isChecked()) {
            const QByteArray identifier = b->property(button_property).toByteArray();
            const QByteArray serverIdentifier = TextAutoGenerateMcpToolsManager::serverIdentifier(identifier);
            if (const auto it = mMcpSelectedTools.constFind(serverIdentifier); !serverIdentifier.isEmpty() && it != mMcpSelectedTools.cend()) {
                for (const QString &toolName : *it) {
                    activeTools.append(TextAutoGenerateMcpToolsManager::toolIdentifier(serverIdentifier, toolName));
                }
            } else {
                activeTools.append(identifier);
            }
        }
    }
    return activeTools;
}

void TextAutoGenerateToolsWidget::disableTools()
{
    for (const auto &b : std::as_const(mListButton)) {
        b->setChecked(false);
    }
}

void TextAutoGenerateToolsWidget::setActivatedTools(const QList<QByteArray> &lst)
{
    disableTools();
    mMcpSelectedTools.clear();
    bool foundTools = false;
    for (const auto &b : lst) {
        // One tool of MCP server: select server button
        const QString mcpToolName = TextAutoGenerateMcpToolsManager::toolName(b);
        const QByteArray identifier =
            mcpToolName.isEmpty() ? b : TextAutoGenerateMcpToolsManager::toolIdentifier(TextAutoGenerateMcpToolsManager::serverIdentifier(b));
        const auto it = std::find_if(mListButton.constBegin(), mListButton.constEnd(), [identifier](QToolButton *button) {
            return button->property(button_property).toByteArray() == identifier;
        });
        if (it != mListButton.cend()) {
            if (!mcpToolName.isEmpty()) {
                mMcpSelectedTools[TextAutoGenerateMcpToolsManager::serverIdentifier(b)].append(mcpToolName);
            }
            (*it)->setChecked(true);
            foundTools = true;
        } else {
            qCWarning(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "Impossible to find button: " << b;
        }
    }
    for (const auto b : std::as_const(mMcpServerButtons)) {
        updateMcpServerButton(TextAutoGenerateMcpToolsManager::serverIdentifier(b->property(button_property).toByteArray()));
    }
    if (foundTools) {
        setVisible(true);
    }
}

#include "moc_textautogeneratetoolswidget.cpp"
