/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamaonlineconfigurewidget.h"
#include "ollamaonlinemanager.h"
#include "ollamaonlinesettings.h"
#include <KAuthorized>
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QFormLayout>
#include <QLineEdit>
#include <QVBoxLayout>
#include <kpasswordlineedit.h>
using namespace Qt::Literals::StringLiterals;
OllamaOnlineConfigureWidget::OllamaOnlineConfigureWidget(OllamaOnlineManager *manager, QWidget *parent)
    : QWidget{parent}
    , mName(new QLineEdit(this))
    , mServerUrl(new QLineEdit(this))
    , mApiKey(new KPasswordLineEdit(this))
    , mManager(manager)
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    auto formLayout = new QFormLayout;
    formLayout->setObjectName(u"mainLayout"_s);
    formLayout->setContentsMargins({});
    mainLayout->addLayout(formLayout);

    mName->setObjectName(u"mName"_s);
    KLineEditEventHandler::catchReturnKey(mName);
    formLayout->addRow(i18n("Name:"), mName);

    mServerUrl->setObjectName(u"mServerUrl"_s);
    KLineEditEventHandler::catchReturnKey(mServerUrl);
    formLayout->addRow(i18n("Server Url:"), mServerUrl);
    mServerUrl->setPlaceholderText(u"https://ollama.com"_s);

    mApiKey->setObjectName(u"mApiKey"_s);
    mApiKey->setRevealPasswordMode(KAuthorized::authorize(u"lineedit_reveal_password"_s) ? KPassword::RevealMode::OnlyNew : KPassword::RevealMode::Never);
    KLineEditEventHandler::catchReturnKey(mApiKey->lineEdit());
    formLayout->addRow(i18n("Api Key:"), mApiKey);

    loadSettings();
}

OllamaOnlineConfigureWidget::~OllamaOnlineConfigureWidget() = default;

void OllamaOnlineConfigureWidget::loadSettings()
{
    mName->setText(mManager->ollamaOnlineSettings()->displayName());
    mServerUrl->setText(mManager->ollamaOnlineSettings()->serverUrl().toString());
}

void OllamaOnlineConfigureWidget::saveSettings()
{
    mManager->ollamaOnlineSettings()->setDisplayName(mName->text());
    mManager->ollamaOnlineSettings()->setServerUrl(QUrl(mServerUrl->text()));
}

#include "moc_ollamaonlineconfigurewidget.cpp"
