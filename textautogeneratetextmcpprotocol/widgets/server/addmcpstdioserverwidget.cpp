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
    mainLayout->addRow(i18n("Command:"), mCommandLineEdit);
    KLineEditEventHandler::catchReturnKey(mCommandLineEdit);
    mCommandLineEdit->setClearButtonEnabled(true);

    mArgumentsLineEdit->setObjectName(u"mArgumentsLineEdit"_s);
    mainLayout->addRow(i18n("Arguments:"), mArgumentsLineEdit);
    KLineEditEventHandler::catchReturnKey(mArgumentsLineEdit);
    mArgumentsLineEdit->setClearButtonEnabled(true);

    connect(mCommandLineEdit, &QLineEdit::textChanged, this, &AddMcpStdioServerWidget::settingChanged);
    connect(mArgumentsLineEdit, &QLineEdit::textChanged, this, &AddMcpStdioServerWidget::settingChanged);
}

AddMcpStdioServerWidget::~AddMcpStdioServerWidget() = default;

void AddMcpStdioServerWidget::setStdioInfo(const StdioInfo &info)
{
    mCommandLineEdit->setText(info.command);
    mArgumentsLineEdit->setText(info.arguments);
}

bool AddMcpStdioServerWidget::isValid() const
{
    return !mCommandLineEdit->text().isEmpty();
}

void AddMcpStdioServerWidget::saveSettings(TextAutoGenerateTextMcpProtocolCore::McpServer &server)
{
    server.setCommand(mCommandLineEdit->text());
    server.setArguments(mArgumentsLineEdit->text());
}

void AddMcpStdioServerWidget::loadSettings(const TextAutoGenerateTextMcpProtocolCore::McpServer &server)
{
    mArgumentsLineEdit->setText(server.arguments());
    mCommandLineEdit->setText(server.command());
}

AddMcpStdioServerWidget::StdioInfo AddMcpStdioServerWidget::stdioInfo() const
{
    const AddMcpStdioServerWidget::StdioInfo info{
        .command = mCommandLineEdit->text(),
        .arguments = mArgumentsLineEdit->text(),
    };
    return info;
}

#include "moc_addmcpstdioserverwidget.cpp"
