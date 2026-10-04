/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextconfiguremcpserverswidget.h"
#include "core/textautogeneratemanager.h"
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
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mMcpServerWidget->setObjectName(u"mMcpServerWidget"_s);
    mainLayout->addWidget(mMcpServerWidget);
    connect(mMcpServerWidget,
            &TextAutoGenerateTextMcpProtocolWidgets::McpServerWidget::settingsChanged,
            this,
            &TextAutoGenerateTextConfigureMcpServersWidget::settingsChanged);
    load();
}

TextAutoGenerateTextConfigureMcpServersWidget::~TextAutoGenerateTextConfigureMcpServersWidget() = default;

void TextAutoGenerateTextConfigureMcpServersWidget::load()
{
    if (mManager) {
        mMcpServerModel->setMcpServers(mManager->textAutoGenerateTextMcpServerManager()->mcpServerModel()->mcpServers());
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
}

#include "moc_textautogeneratetextconfiguremcpserverswidget.cpp"
