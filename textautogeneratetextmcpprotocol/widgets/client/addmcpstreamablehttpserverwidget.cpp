/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "addmcpstreamablehttpserverwidget.h"
#include "addmcpstreamablehttpserverheaderwidget.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <KPasswordLineEdit>
#include <QFormLayout>
#include <QLineEdit>
#include <TextAutoGenerateTextMcpProtocolCore/McpServer>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolWidgets;
AddMcpStreamableHttpServerWidget::AddMcpStreamableHttpServerWidget(QWidget *parent)
    : AddMcpServerBaseWidget{parent}
    , mServerUrlLineEdit(new QLineEdit(this))
    , mHttpServerHeaderWidget(new AddMcpStreamableHttpServerHeaderWidget(this))
    , mAuthTokenLineEdit(new KPasswordLineEdit(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins(QMargins{});

    mServerUrlLineEdit->setObjectName(u"mServerUrlLineEdit"_s);
    mServerUrlLineEdit->setClearButtonEnabled(true);
    mainLayout->addRow(i18nc("@label:textbox", "URL:"), mServerUrlLineEdit);
    KLineEditEventHandler::catchReturnKey(mServerUrlLineEdit);

    mHttpServerHeaderWidget->setObjectName(u"mHttpServerHeaderWidget"_s);
    mainLayout->addRow(i18nc("@label", "Headers:"), mHttpServerHeaderWidget);
    mAuthTokenLineEdit->setObjectName(u"mAuthTokenLineEdit"_s);
    mAuthTokenLineEdit->setToolTip(i18nc("@info:tooltip", "Sent as \"Authorization: Bearer\" header. Stored in the system wallet."));
    mainLayout->addRow(i18nc("@label:textbox", "Authentication token:"), mAuthTokenLineEdit);
    KLineEditEventHandler::catchReturnKey(mAuthTokenLineEdit->lineEdit());

    connect(mServerUrlLineEdit, &QLineEdit::textChanged, this, &AddMcpStreamableHttpServerWidget::settingChanged);
}

AddMcpStreamableHttpServerWidget::~AddMcpStreamableHttpServerWidget() = default;

bool AddMcpStreamableHttpServerWidget::isValid() const
{
    const QString text = mServerUrlLineEdit->text().trimmed();
    if (text.isEmpty()) {
        return false;
    }
    const QUrl url = QUrl::fromUserInput(text);
    return url.isValid() && !url.host().isEmpty() && (url.scheme() == "http"_L1 || url.scheme() == "https"_L1);
}

void AddMcpStreamableHttpServerWidget::saveSettings(TextAutoGenerateTextMcpProtocolCore::McpServer &server)
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings = server.settings();
    settings.setServerUrl(QUrl::fromUserInput(mServerUrlLineEdit->text().trimmed()));
    settings.setHeaders(mHttpServerHeaderWidget->headers());
    settings.setAuthToken(mAuthTokenLineEdit->password().trimmed().toUtf8());
    // Remove settings from another transport type
    settings.setCommand({});
    settings.setArguments({});
    settings.setEnvironments({});
    server.setSettings(std::move(settings));
}

void AddMcpStreamableHttpServerWidget::loadSettings(const TextAutoGenerateTextMcpProtocolCore::McpServer &server)
{
    mServerUrlLineEdit->setText(server.settings().serverUrl().toString());
    mHttpServerHeaderWidget->setHeaders(server.settings().headers());
    mAuthTokenLineEdit->setPassword(QString::fromUtf8(server.settings().authToken()));
}

#include "moc_addmcpstreamablehttpserverwidget.cpp"
