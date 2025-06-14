/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratenetworkpluginconfigurewidget.h"

#include <KAuthorized>
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <KPasswordLineEdit>
#include <QFormLayout>

using namespace TextAutoGenerateText;
TextAutoGenerateNetworkPluginConfigureWidget::TextAutoGenerateNetworkPluginConfigureWidget(QWidget *parent)
    : QWidget{parent}
    , mApiKey(new KPasswordLineEdit(this))
    , mInstanceName(new QLineEdit(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});
    mApiKey->setObjectName(QStringLiteral("mApiKey"));
    mInstanceName->setObjectName(QStringLiteral("mInstanceName"));
    mInstanceName->setClearButtonEnabled(true);

    mApiKey->setObjectName(QStringLiteral("mPasswordLineEdit"));
    mApiKey->setRevealPasswordMode(KAuthorized::authorize(QStringLiteral("lineedit_reveal_password")) ? KPassword::RevealMode::OnlyNew
                                                                                                      : KPassword::RevealMode::Never);

    mainLayout->addRow(i18n("Name:"), mInstanceName);

    mainLayout->addRow(i18n("Api Key:"), mApiKey);
    KLineEditEventHandler::catchReturnKey(mApiKey->lineEdit());
    KLineEditEventHandler::catchReturnKey(mInstanceName);
}

TextAutoGenerateNetworkPluginConfigureWidget::~TextAutoGenerateNetworkPluginConfigureWidget() = default;

void TextAutoGenerateNetworkPluginConfigureWidget::setApiKey(const QString &key)
{
    mApiKey->setPassword(key);
}

QString TextAutoGenerateNetworkPluginConfigureWidget::apiKey() const
{
    return mApiKey->password();
}

void TextAutoGenerateNetworkPluginConfigureWidget::setInstanceName(const QString &name)
{
    mInstanceName->setText(name);
}

QString TextAutoGenerateNetworkPluginConfigureWidget::instanceName() const
{
    return mInstanceName->text();
}

#include "moc_textautogeneratenetworkpluginconfigurewidget.cpp"
