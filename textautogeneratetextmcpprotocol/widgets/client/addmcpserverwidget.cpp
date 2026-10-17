/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "addmcpserverwidget.h"
#include "client/addmcpserverrootswidget.h"
#include "client/addmcpsseserverwidget.h"
#include "client/addmcpstdioserverwidget.h"
#include "client/addmcpstreamablehttpserverwidget.h"
#include "common/selecttypecombobox.h"
#include "textautogeneratetextmcpprotocol_widgets_debug.h"
#include <KIconButton>
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QFormLayout>
#include <QLineEdit>
#include <QStackedWidget>

using namespace TextAutoGenerateTextMcpProtocolWidgets;
using namespace Qt::Literals::StringLiterals;
AddMcpServerWidget::AddMcpServerWidget(QWidget *parent)
    : QWidget{parent}
    , mServerNameLineEdit(new QLineEdit(this))
    , mSelectTypeComboBox(new SelectTypeComboBox(this))
    , mStackedWidget(new QStackedWidget(this))
    , mAddMcpSseServerWidget(new AddMcpSseServerWidget(this))
    , mAddMcpStdioServerWidget(new AddMcpStdioServerWidget(this))
    , mAddMcpStreamableHttpServerWidget(new AddMcpStreamableHttpServerWidget(this))
    , mAddMcpServerRootsWidget(new AddMcpServerRootsWidget(this))
    , mIconName(new KIconButton(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mServerNameLineEdit->setObjectName(u"mServerNameLineEdit"_s);
    mainLayout->addRow(i18nc("@label:textbox", "Name:"), mServerNameLineEdit);
    KLineEditEventHandler::catchReturnKey(mServerNameLineEdit);

    mIconName->setObjectName(u"mIconName"_s);
    mainLayout->addRow(i18nc("@label:textbox", "Icon:"), mIconName);

    mSelectTypeComboBox->setObjectName(u"mSelectTypeComboBox"_s);
    mainLayout->addRow(i18nc("@label:listbox", "Type:"), mSelectTypeComboBox);
    connect(mSelectTypeComboBox, &SelectTypeComboBox::activated, this, &AddMcpServerWidget::changeType);

    mStackedWidget->setObjectName(u"mStackedWidget"_s);
    mainLayout->addRow(mStackedWidget);

    mAddMcpSseServerWidget->setObjectName(u"mAddMcpSseServerWidget"_s);
    mAddMcpStdioServerWidget->setObjectName(u"mAddMcpStdioServerWidget"_s);
    mAddMcpStreamableHttpServerWidget->setObjectName(u"mAddMcpStreamableHttpServerWidget"_s);

    mStackedWidget->addWidget(mAddMcpSseServerWidget);
    mStackedWidget->addWidget(mAddMcpStdioServerWidget);
    mStackedWidget->addWidget(mAddMcpStreamableHttpServerWidget);

    mAddMcpServerRootsWidget->setObjectName(u"mAddMcpServerRootsWidget"_s);
    mainLayout->addRow(i18nc("@label", "Allowed folders:"), mAddMcpServerRootsWidget);

    mServerNameLineEdit->setClearButtonEnabled(true);

    connect(mServerNameLineEdit, &QLineEdit::textChanged, this, &AddMcpServerWidget::checkValidSettings);
    connect(mAddMcpSseServerWidget, &AddMcpSseServerWidget::settingChanged, this, &AddMcpServerWidget::checkValidSettings);
    connect(mAddMcpStdioServerWidget, &AddMcpStdioServerWidget::settingChanged, this, &AddMcpServerWidget::checkValidSettings);
    connect(mAddMcpStreamableHttpServerWidget, &AddMcpStreamableHttpServerWidget::settingChanged, this, &AddMcpServerWidget::checkValidSettings);
}

AddMcpServerWidget::~AddMcpServerWidget() = default;

void AddMcpServerWidget::setServerInfo(const TextAutoGenerateTextMcpProtocolCore::McpServer &server)
{
    mServer = server;
    mServerNameLineEdit->setText(server.name());
    const auto serverType = server.transportType();
    switch (serverType) {
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Sse:
        mAddMcpSseServerWidget->loadSettings(server);
        break;
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Stdio:
        mAddMcpStdioServerWidget->loadSettings(server);
        break;
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::StreamableHttp:
        mAddMcpStreamableHttpServerWidget->loadSettings(server);
        break;
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Unknown:
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLWIDGETS_LOG) << "Protocol is unknown. It's a bug";
        break;
    }
    mAddMcpServerRootsWidget->setRoots(server.settings().roots());
    mSelectTypeComboBox->setType(serverType);
    mIconName->setIcon(server.iconName());
    updateWidget(serverType);
    checkValidSettings();
}

TextAutoGenerateTextMcpProtocolCore::McpServer AddMcpServerWidget::serverInfo() const
{
    TextAutoGenerateTextMcpProtocolCore::McpServer server = mServer;
    if (server.identifier().isEmpty()) {
        server.createUniqueIdentifier();
    }
    server.setName(mServerNameLineEdit->text().trimmed());
    const auto serverType = mSelectTypeComboBox->type();
    server.setTransportType(serverType);

    switch (serverType) {
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Sse:
        mAddMcpSseServerWidget->saveSettings(server);
        break;
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Stdio:
        mAddMcpStdioServerWidget->saveSettings(server);
        break;
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::StreamableHttp:
        mAddMcpStreamableHttpServerWidget->saveSettings(server);
        break;
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Unknown:
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLWIDGETS_LOG) << "Protocol is unknown. It's a bug";
        break;
    }
    server.setIconName(mIconName->icon());
    // Roots are used by all transport types
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings = server.settings();
    settings.setRoots(mAddMcpServerRootsWidget->roots());
    server.setSettings(std::move(settings));
    return server;
}

void AddMcpServerWidget::updateWidget(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType type)
{
    switch (type) {
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Sse:
        mStackedWidget->setCurrentWidget(mAddMcpSseServerWidget);
        break;
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Stdio:
        mStackedWidget->setCurrentWidget(mAddMcpStdioServerWidget);
        break;
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::StreamableHttp:
        mStackedWidget->setCurrentWidget(mAddMcpStreamableHttpServerWidget);
        break;
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Unknown:
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLWIDGETS_LOG) << "Protocol is unknown. It's a bug";
        break;
    }
}
void AddMcpServerWidget::changeType()
{
    updateWidget(mSelectTypeComboBox->type());
    checkValidSettings();
}

void AddMcpServerWidget::checkValidSettings()
{
    bool settingsIsValid = false;
    switch (mSelectTypeComboBox->type()) {
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Sse:
        settingsIsValid = mAddMcpSseServerWidget->isValid();
        break;
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Stdio:
        settingsIsValid = mAddMcpStdioServerWidget->isValid();
        break;
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::StreamableHttp:
        settingsIsValid = mAddMcpStreamableHttpServerWidget->isValid();
        break;
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Unknown:
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLWIDGETS_LOG) << "Protocol is unknown. It's a bug";
        break;
    }
    Q_EMIT buttonOkEnabled(!mServerNameLineEdit->text().trimmed().isEmpty() && settingsIsValid);
}

#include "moc_addmcpserverwidget.cpp"
