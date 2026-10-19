/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolserverconfigurewidget.h"
#include "server/mcpprotocolserverconfiguretokenwidget.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QCheckBox>
#include <QFormLayout>
#include <QLineEdit>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerUtils>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolWidgets;
McpProtocolServerConfigureWidget::McpProtocolServerConfigureWidget(QWidget *parent)
    : QWidget{parent}
    , mServerUrlLineEdit(new QLineEdit(this))
    , mRequireAuthenticationCheckBox(new QCheckBox(i18nc("@option:check", "Require authentication token"), this))
    , mTokenWidget(new McpProtocolServerConfigureTokenWidget(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mServerUrlLineEdit->setObjectName(u"mServerUrlLineEdit"_s);
    mServerUrlLineEdit->setClearButtonEnabled(true);
    mServerUrlLineEdit->setPlaceholderText(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerUtils::defaultServerUrl().toString());
    mServerUrlLineEdit->setToolTip(i18nc("@info:tooltip", "Server listens only on a local IP address, e.g. http://127.0.0.1:8765/mcp"));
    mainLayout->addRow(i18nc("@label:textbox", "URL:"), mServerUrlLineEdit);
    KLineEditEventHandler::catchReturnKey(mServerUrlLineEdit);

    mRequireAuthenticationCheckBox->setObjectName(u"mRequireAuthenticationCheckBox"_s);
    mRequireAuthenticationCheckBox->setToolTip(
        i18nc("@info:tooltip", "Clients must send this token as \"Authorization: Bearer\" header. Token is stored in the system wallet."));
    mainLayout->addRow(mRequireAuthenticationCheckBox);

    mTokenWidget->setObjectName(u"mTokenWidget"_s);
    mTokenWidget->setEnabled(false);
    mainLayout->addRow(mTokenWidget);

    connect(mServerUrlLineEdit, &QLineEdit::textChanged, this, &McpProtocolServerConfigureWidget::settingsChanged);
    connect(mRequireAuthenticationCheckBox, &QCheckBox::toggled, this, &McpProtocolServerConfigureWidget::slotRequireAuthenticationToggled);
    connect(mTokenWidget, &McpProtocolServerConfigureTokenWidget::authTokenChanged, this, &McpProtocolServerConfigureWidget::settingsChanged);
}

McpProtocolServerConfigureWidget::~McpProtocolServerConfigureWidget() = default;

void McpProtocolServerConfigureWidget::slotRequireAuthenticationToggled(bool checked)
{
    mTokenWidget->setEnabled(checked);
    if (checked && mTokenWidget->authToken().isEmpty()) {
        mTokenWidget->setAuthToken(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerUtils::generateAuthToken());
    }
    Q_EMIT settingsChanged();
}

void McpProtocolServerConfigureWidget::setSettings(const TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings &settings)
{
    mServerUrlLineEdit->setText(settings.serverUrl().toString());
    // Set token first: toggling checkbox must not generate a new one
    mTokenWidget->setAuthToken(settings.authToken());
    mRequireAuthenticationCheckBox->setChecked(!settings.authToken().isEmpty());
    Q_EMIT settingsChanged();
}

TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings McpProtocolServerConfigureWidget::settings() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    settings.setServerUrl(QUrl(mServerUrlLineEdit->text().trimmed()));
    if (mRequireAuthenticationCheckBox->isChecked()) {
        settings.setAuthToken(mTokenWidget->authToken());
    }
    return settings;
}

bool McpProtocolServerConfigureWidget::isValid() const
{
    // See McpServerStreamableHttp::connection()
    const QUrl url(mServerUrlLineEdit->text().trimmed());
    if (!url.isValid() || url.scheme() != "http"_L1 || url.port() <= 0) {
        return false;
    }
    return !mRequireAuthenticationCheckBox->isChecked() || !mTokenWidget->authToken().isEmpty();
}

#include "moc_mcpprotocolserverconfigurewidget.cpp"
