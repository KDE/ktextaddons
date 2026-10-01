/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "addmcpsseserverwidget.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QFormLayout>
#include <QLineEdit>
#include <TextAutoGenerateTextMcpProtocolCore/McpServer>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolWidgets;
AddMcpSseServerWidget::AddMcpSseServerWidget(QWidget *parent)
    : AddMcpServerBaseWidget{parent}
    , mServerUrlLineEdit(new QLineEdit(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins(QMargins{});

    mServerUrlLineEdit->setObjectName(u"mServerUrlLineEdit"_s);
    mServerUrlLineEdit->setClearButtonEnabled(true);
    mainLayout->addRow(i18nc("@label:textbox", "Url:"), mServerUrlLineEdit);
    KLineEditEventHandler::catchReturnKey(mServerUrlLineEdit);
    connect(mServerUrlLineEdit, &QLineEdit::textChanged, this, &AddMcpSseServerWidget::settingChanged);
}

AddMcpSseServerWidget::~AddMcpSseServerWidget() = default;

void AddMcpSseServerWidget::setUrl(const QString &str)
{
    mServerUrlLineEdit->setText(str);
}

QString AddMcpSseServerWidget::url() const
{
    return mServerUrlLineEdit->text();
}

bool AddMcpSseServerWidget::isValid() const
{
    const QString text = mServerUrlLineEdit->text().trimmed();
    if (text.isEmpty()) {
        return false;
    }
    const QUrl url = QUrl::fromUserInput(text);
    return url.isValid() && !url.host().isEmpty() && (url.scheme() == "http"_L1 || url.scheme() == "https"_L1);
}

void AddMcpSseServerWidget::saveSettings(TextAutoGenerateTextMcpProtocolCore::McpServer &server)
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings = server.settings();
    settings.setServerUrl(QUrl::fromUserInput(mServerUrlLineEdit->text().trimmed()));
    server.setSettings(std::move(settings));
}

void AddMcpSseServerWidget::loadSettings(const TextAutoGenerateTextMcpProtocolCore::McpServer &server)
{
    mServerUrlLineEdit->setText(server.settings().serverUrl().toString());
}

#include "moc_addmcpsseserverwidget.cpp"
