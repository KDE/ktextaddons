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
#include <QToolButton>
#include <TextAddonsWidgets/TextAddonsWidgetFlowLayout>
#include <TextAutoGenerateTextMcpProtocolCore/McpServerManager>
#include <TextAutoGenerateTextMcpProtocolCore/McpServerModel>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
namespace
{
constexpr const char *button_property("identifier");
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
    for (const auto &server : servers) {
        if (!server.enabled() || !server.isValid()) {
            continue;
        }
        const QByteArray serverIdentifier = server.identifier();
        auto b = new QToolButton(this);
        b->setText(server.name());
        b->setIcon(QIcon::fromTheme(u"network-server-symbolic"_s));
        b->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        b->setAutoRaise(true);
        b->setCheckable(true);
        b->setProperty(button_property, TextAutoGenerateMcpToolsManager::toolIdentifier(serverIdentifier));
        connect(b, &QToolButton::toggled, this, [this, serverIdentifier](bool checked) {
            if (checked) {
                // Connect now: tools will be ready when message is sent
                mManager->textAutoGenerateMcpToolsManager()->connectServer(serverIdentifier);
            }
        });
        layout()->addWidget(b);
        mListButton.append(b);
        mMcpServerButtons.append(b);
        b->setChecked(checkedServers.contains(b->property(button_property).toByteArray()));
        updateMcpServerButton(serverIdentifier);
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
        status = i18np("1 tool", "%1 tools", toolsManager->tools(serverIdentifier).count());
        break;
    case TextAutoGenerateMcpToolsManager::Status::Error:
        status = i18n("Error: %1", toolsManager->errorString(serverIdentifier));
        break;
    }
    (*it)->setToolTip(i18n("Tools of MCP server \"%1\" (%2)", (*it)->text(), status));
}

TextAutoGenerateToolsWidget::~TextAutoGenerateToolsWidget() = default;

QList<QByteArray> TextAutoGenerateToolsWidget::generateListOfActiveTools() const
{
    QList<QByteArray> activeTools;
    activeTools.reserve(mListButton.count());
    for (const auto b : std::as_const(mListButton)) {
        if (b->isChecked()) {
            activeTools.append(b->property(button_property).toByteArray());
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
    bool foundTools = false;
    for (const auto &b : lst) {
        const auto it = std::find_if(mListButton.constBegin(), mListButton.constEnd(), [b](QToolButton *button) {
            return button->property(button_property).toByteArray() == b;
        });
        if (it != mListButton.cend()) {
            (*it)->setChecked(true);
            foundTools = true;
        } else {
            qCWarning(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "Impossible to find button: " << b;
        }
    }
    if (foundTools) {
        setVisible(true);
    }
}

#include "moc_textautogeneratetoolswidget.cpp"
