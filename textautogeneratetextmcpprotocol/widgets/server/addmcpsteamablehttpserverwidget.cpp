/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "addmcpsteamablehttpserverwidget.h"
#include "addmcpsteamablehttpserverheaderwidget.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QFormLayout>
#include <QLineEdit>
#include <TextAutoGenerateTextMcpProtocolCore/McpServer>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolWidgets;
AddMcpSteamableHttpServerWidget::AddMcpSteamableHttpServerWidget(QWidget *parent)
    : AddMcpServerBaseWidget{parent}
    , mServerUrlLineEdit(new QLineEdit(this))
    , mHttpServerHeaderWidget(new AddMcpSteamableHttpServerHeaderWidget(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins(QMargins{});

    mServerUrlLineEdit->setObjectName(u"mServerUrlLineEdit"_s);
    mServerUrlLineEdit->setClearButtonEnabled(true);
    mainLayout->addRow(i18n("Url:"), mServerUrlLineEdit);
    KLineEditEventHandler::catchReturnKey(mServerUrlLineEdit);

    mHttpServerHeaderWidget->setObjectName(u"mHttpServerHeaderWidget"_s);
    mainLayout->addRow(i18n("Headers:"), mHttpServerHeaderWidget);

    connect(mServerUrlLineEdit, &QLineEdit::textChanged, this, &AddMcpSteamableHttpServerWidget::settingChanged);
}

AddMcpSteamableHttpServerWidget::~AddMcpSteamableHttpServerWidget() = default;

void AddMcpSteamableHttpServerWidget::setUrl(const QString &str)
{
    mServerUrlLineEdit->setText(str);
}

QString AddMcpSteamableHttpServerWidget::url() const
{
    return mServerUrlLineEdit->text();
}

bool AddMcpSteamableHttpServerWidget::isValid() const
{
    return !mServerUrlLineEdit->text().isEmpty();
}

void AddMcpSteamableHttpServerWidget::saveSettings(TextAutoGenerateTextMcpProtocolCore::McpServer &server)
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    settings.setServerUrl(QUrl(mServerUrlLineEdit->text()));
    settings.setHeaders(mHttpServerHeaderWidget->headers());
    server.setSettings(settings);
}

void AddMcpSteamableHttpServerWidget::loadSettings(const TextAutoGenerateTextMcpProtocolCore::McpServer &server)
{
    mServerUrlLineEdit->setText(server.settings().serverUrl().toString());
    mHttpServerHeaderWidget->setHeaders(server.settings().headers());
}

#include "moc_addmcpsteamablehttpserverwidget.cpp"
