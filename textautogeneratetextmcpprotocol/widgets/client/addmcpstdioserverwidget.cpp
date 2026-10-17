/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "addmcpstdioserverwidget.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QFormLayout>
#include <QLineEdit>
#include <TextAutoGenerateTextMcpProtocolCore/McpServer>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolWidgets;
AddMcpStdioServerWidget::AddMcpStdioServerWidget(QWidget *parent)
    : AddMcpServerBaseWidget{parent}
    , mCommandLineEdit(new QLineEdit(this))
    , mArgumentsLineEdit(new QLineEdit(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins(QMargins{});

    mCommandLineEdit->setObjectName(u"mCommandLineEdit"_s);
    mainLayout->addRow(i18nc("@label:textbox", "Command:"), mCommandLineEdit);
    KLineEditEventHandler::catchReturnKey(mCommandLineEdit);
    mCommandLineEdit->setClearButtonEnabled(true);

    mArgumentsLineEdit->setObjectName(u"mArgumentsLineEdit"_s);
    mainLayout->addRow(i18nc("@label:textbox", "Arguments:"), mArgumentsLineEdit);
    KLineEditEventHandler::catchReturnKey(mArgumentsLineEdit);
    mArgumentsLineEdit->setClearButtonEnabled(true);

    connect(mCommandLineEdit, &QLineEdit::textChanged, this, &AddMcpStdioServerWidget::settingChanged);
    connect(mArgumentsLineEdit, &QLineEdit::textChanged, this, &AddMcpStdioServerWidget::settingChanged);
}

AddMcpStdioServerWidget::~AddMcpStdioServerWidget() = default;

bool AddMcpStdioServerWidget::isValid() const
{
    return !mCommandLineEdit->text().trimmed().isEmpty();
}

void AddMcpStdioServerWidget::saveSettings(TextAutoGenerateTextMcpProtocolCore::McpServer &server)
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings = server.settings();
    settings.setCommand(mCommandLineEdit->text().trimmed());
    settings.setArguments(mArgumentsLineEdit->text().trimmed());
    // Remove settings from another transport type
    settings.setServerUrl({});
    settings.setHeaders({});

    server.setSettings(std::move(settings));
}

void AddMcpStdioServerWidget::loadSettings(const TextAutoGenerateTextMcpProtocolCore::McpServer &server)
{
    const auto settings = server.settings();
    mArgumentsLineEdit->setText(settings.arguments());
    mCommandLineEdit->setText(settings.command());
}

#include "moc_addmcpstdioserverwidget.cpp"
