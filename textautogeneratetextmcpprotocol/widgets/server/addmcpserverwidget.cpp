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

using namespace TextAutoGenerateTextMcpProtocolWidgets;
using namespace Qt::Literals::StringLiterals;
AddMcpServerWidget::AddMcpServerWidget(QWidget *parent)
    : QWidget{parent}
    , mServerNameLineEdit(new QLineEdit(this))
    , mServerUrlLineEdit(new QLineEdit(this))
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
    mainLayout->addWidget(mStackedWidget);

    mAddMcpSseServerWidget->setObjectName(u"mAddMcpSseServerWidget"_s);
    mAddMcpStdioServerWidget->setObjectName(u"mAddMcpStdioServerWidget"_s);
    mAddMcpSteamableHttpServerWidget->setObjectName(u"mAddMcpSteamableHttpServerWidget"_s);

    mStackedWidget->addWidget(mAddMcpSseServerWidget);
    mStackedWidget->addWidget(mAddMcpStdioServerWidget);
    mStackedWidget->addWidget(mAddMcpSteamableHttpServerWidget);

    mServerUrlLineEdit->setObjectName(u"mServerUrlLineEdit"_s);
    mainLayout->addRow(i18nc("@label:textbox", "Url:"), mServerUrlLineEdit);
    KLineEditEventHandler::catchReturnKey(mServerUrlLineEdit);
    mServerUrlLineEdit->setClearButtonEnabled(true);
    mServerNameLineEdit->setClearButtonEnabled(true);

    connect(mServerNameLineEdit, &QLineEdit::textChanged, this, &AddMcpServerWidget::checkValidSettings);
    connect(mServerUrlLineEdit, &QLineEdit::textChanged, this, &AddMcpServerWidget::checkValidSettings);
}

AddMcpServerWidget::~AddMcpServerWidget() = default;

void AddMcpServerWidget::changeType()
{
    switch (mSelectTypeComboBox->type()) {
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::ProtocolType::Sse:
        mStackedWidget->setCurrentWidget(mAddMcpSseServerWidget);
        break;
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::ProtocolType::Stdio:
        mStackedWidget->setCurrentWidget(mAddMcpStdioServerWidget);
        break;
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::ProtocolType::StreamableHttp:
        mStackedWidget->setCurrentWidget(mAddMcpSteamableHttpServerWidget);
        break;
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::ProtocolType::Unknown:
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLWIDGETS_LOG) << "Protocol is unknown. It's a bug";
        break;
    }
}

void AddMcpServerWidget::checkValidSettings()
{
    Q_EMIT buttonOkEnabled(!mServerNameLineEdit->text().trimmed().isEmpty() && !mServerUrlLineEdit->text().trimmed().isEmpty());
}

void AddMcpServerWidget::setServerWidgetInfo(const McpServerWidgetInfo &info)
{
    mServerNameLineEdit->setText(info.name);
    mServerUrlLineEdit->setText(info.serverUrl);
}

AddMcpServerWidget::McpServerWidgetInfo AddMcpServerWidget::serverWidgetInfo() const
{
    const AddMcpServerWidget::McpServerWidgetInfo info{
        .name = mServerNameLineEdit->text(),
        .serverUrl = mServerUrlLineEdit->text(),
    };
    return info;
}

#include "moc_addmcpserverwidget.cpp"
