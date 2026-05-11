/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "addmcpserverwidget.h"
#include "common/selecttypecombobox.h"
#include "server/addmcpsseserverwidget.h"
#include "server/addmcpstdioserverwidget.h"
#include "server/addmcpsteamablehttpserverwidget.h"
#include "textautogeneratetextmcpprotocol_widgets_debug.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QFormLayout>
#include <QLineEdit>
#include <QStackedWidget>
#include <TextAutoGenerateTextMcpProtocolCore/McpServer>

using namespace TextAutoGenerateTextMcpProtocolWidgets;
using namespace Qt::Literals::StringLiterals;
AddMcpServerWidget::AddMcpServerWidget(QWidget *parent)
    : QWidget{parent}
    , mServerNameLineEdit(new QLineEdit(this))
    , mSelectTypeComboBox(new SelectTypeComboBox(this))
    , mStackedWidget(new QStackedWidget(this))
    , mAddMcpSseServerWidget(new AddMcpSseServerWidget(this))
    , mAddMcpStdioServerWidget(new AddMcpStdioServerWidget(this))
    , mAddMcpSteamableHttpServerWidget(new AddMcpSteamableHttpServerWidget(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mServerNameLineEdit->setObjectName(u"mServerNameLineEdit"_s);
    mainLayout->addRow(i18nc("@label:textbox", "Name:"), mServerNameLineEdit);
    KLineEditEventHandler::catchReturnKey(mServerNameLineEdit);

    mSelectTypeComboBox->setObjectName(u"mSelectTypeComboBox"_s);
    mainLayout->addRow(i18nc("@label:textbox", "Type:"), mSelectTypeComboBox);
    connect(mSelectTypeComboBox, &SelectTypeComboBox::activated, this, &AddMcpServerWidget::changeType);

    mStackedWidget->setObjectName(u"mStackedWidget"_s);
    mainLayout->addRow(mStackedWidget);

    mAddMcpSseServerWidget->setObjectName(u"mAddMcpSseServerWidget"_s);
    mAddMcpStdioServerWidget->setObjectName(u"mAddMcpStdioServerWidget"_s);
    mAddMcpSteamableHttpServerWidget->setObjectName(u"mAddMcpSteamableHttpServerWidget"_s);

    mStackedWidget->addWidget(mAddMcpSseServerWidget);
    mStackedWidget->addWidget(mAddMcpStdioServerWidget);
    mStackedWidget->addWidget(mAddMcpSteamableHttpServerWidget);

    mServerNameLineEdit->setClearButtonEnabled(true);

    connect(mServerNameLineEdit, &QLineEdit::textChanged, this, &AddMcpServerWidget::checkValidSettings);
    connect(mAddMcpSseServerWidget, &AddMcpSseServerWidget::settingChanged, this, &AddMcpServerWidget::checkValidSettings);
    connect(mAddMcpStdioServerWidget, &AddMcpStdioServerWidget::settingChanged, this, &AddMcpServerWidget::checkValidSettings);
    connect(mAddMcpSteamableHttpServerWidget, &AddMcpSteamableHttpServerWidget::settingChanged, this, &AddMcpServerWidget::checkValidSettings);
}

AddMcpServerWidget::~AddMcpServerWidget() = default;

void AddMcpServerWidget::setServerInfo(const TextAutoGenerateTextMcpProtocolCore::McpServer &server)
{
    mServer = server;
    mServerNameLineEdit->setText(server.name());
    switch (mSelectTypeComboBox->type()) {
    case TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType::Sse:
        mAddMcpSseServerWidget->loadSettings(server);
        break;
    case TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType::Stdio:
        mAddMcpStdioServerWidget->loadSettings(server);
        break;
    case TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType::StreamableHttp:
        mAddMcpSteamableHttpServerWidget->loadSettings(server);
        break;
    case TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType::Unknown:
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLWIDGETS_LOG) << "Protocol is unknown. It's a bug";
        break;
    }
}

TextAutoGenerateTextMcpProtocolCore::McpServer AddMcpServerWidget::serverInfo() const
{
    TextAutoGenerateTextMcpProtocolCore::McpServer server = mServer;
    if (server.identifier().isEmpty()) {
        server.createUniqueIdentifier();
    }
    server.setName(mServerNameLineEdit->text());
    const auto serverType = mSelectTypeComboBox->type();
    server.setServerType(serverType);

    switch (serverType) {
    case TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType::Sse:
        mAddMcpSseServerWidget->saveSettings(server);
        break;
    case TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType::Stdio:
        mAddMcpStdioServerWidget->saveSettings(server);
        break;
    case TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType::StreamableHttp:
        mAddMcpSteamableHttpServerWidget->saveSettings(server);
        break;
    case TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType::Unknown:
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLWIDGETS_LOG) << "Protocol is unknown. It's a bug";
        break;
    }
    return server;
}

void AddMcpServerWidget::changeType()
{
    switch (mSelectTypeComboBox->type()) {
    case TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType::Sse:
        mStackedWidget->setCurrentWidget(mAddMcpSseServerWidget);
        break;
    case TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType::Stdio:
        mStackedWidget->setCurrentWidget(mAddMcpStdioServerWidget);
        break;
    case TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType::StreamableHttp:
        mStackedWidget->setCurrentWidget(mAddMcpSteamableHttpServerWidget);
        break;
    case TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType::Unknown:
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLWIDGETS_LOG) << "Protocol is unknown. It's a bug";
        break;
    }
}

void AddMcpServerWidget::checkValidSettings()
{
    bool settingsIsValid = false;
    switch (mSelectTypeComboBox->type()) {
    case TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType::Sse:
        settingsIsValid = mAddMcpSseServerWidget->isValid();
        break;
    case TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType::Stdio:
        settingsIsValid = mAddMcpStdioServerWidget->isValid();
        break;
    case TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType::StreamableHttp:
        settingsIsValid = mAddMcpSteamableHttpServerWidget->isValid();
        break;
    case TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType::Unknown:
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLWIDGETS_LOG) << "Protocol is unknown. It's a bug";
        break;
    }
    Q_EMIT buttonOkEnabled(!mServerNameLineEdit->text().trimmed().isEmpty() && settingsIsValid);
}

#include "moc_addmcpserverwidget.cpp"
