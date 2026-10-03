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
    mainLayout->addRow(i18nc("@label:textbox", "Url:"), mServerUrlLineEdit);
    KLineEditEventHandler::catchReturnKey(mServerUrlLineEdit);

    mHttpServerHeaderWidget->setObjectName(u"mHttpServerHeaderWidget"_s);
    mainLayout->addRow(i18nc("@label", "Headers:"), mHttpServerHeaderWidget);

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
    const QString text = mServerUrlLineEdit->text().trimmed();
    if (text.isEmpty()) {
        return false;
    }
    const QUrl url = QUrl::fromUserInput(text);
    return url.isValid() && !url.host().isEmpty() && (url.scheme() == "http"_L1 || url.scheme() == "https"_L1);
}

void AddMcpSteamableHttpServerWidget::saveSettings(TextAutoGenerateTextMcpProtocolCore::McpServer &server)
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings = server.settings();
    settings.setServerUrl(QUrl::fromUserInput(mServerUrlLineEdit->text().trimmed()));
    settings.setHeaders(mHttpServerHeaderWidget->headers());
    // Remove settings from another transport type
    settings.setCommand({});
    settings.setArguments({});
    settings.setEnvironments({});
    server.setSettings(std::move(settings));
}

void AddMcpSteamableHttpServerWidget::loadSettings(const TextAutoGenerateTextMcpProtocolCore::McpServer &server)
{
    mServerUrlLineEdit->setText(server.settings().serverUrl().toString());
    mHttpServerHeaderWidget->setHeaders(server.settings().headers());
}

#include "moc_addmcpsteamablehttpserverwidget.cpp"
